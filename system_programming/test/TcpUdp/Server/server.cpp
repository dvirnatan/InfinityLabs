#include <stdio.h> /* printf */
#include <stdlib.h>  /* exit */
#include <sys/ioctl.h> /* ioct */
#include <netinet/in.h> /* htons, INDARR_ANY */
#include <errno.h> /* errno */
#include <cstring> /* strcmp */
#include <unistd.h> /* STDIN_FILENO */

#include "utils.hpp"

int main ()
{
   int    i, rc;
   int    fd_tcp, fd_udp, fd_broadcast ,fd_max;
   int    desc_ready, end_server = FALSE;
   int    close_conn;
   char   buffer[80];
   struct sockaddr_in   udp_addr, tcp_addr, broadcast_addr;
   struct timeval       timeout;
   fd_set 		master_set, working_set;

   fd_udp = CreateServer(UDP_PORT, SOCK_DGRAM, INADDR_ANY, &udp_addr);

	fd_tcp = CreateServer(TCP_PORT, SOCK_STREAM ,INADDR_ANY, &tcp_addr);

	fd_broadcast = CreateServer(BROAD_PORT, SOCK_DGRAM, INADDR_BROADCAST, &broadcast_addr);

   rc = listen(fd_tcp, 32);
   if (rc < 0)

   {
      perror("listen() failed");
      close(fd_tcp);
      exit(-1);
   }

   FD_ZERO(&master_set);
   FD_SET(STDIN_FILENO, &master_set);
   FD_SET(fd_broadcast, &master_set);
   FD_SET(fd_udp, &master_set);
   FD_SET(fd_tcp, &master_set);
   fd_max = max(fd_tcp, max(fd_udp, fd_broadcast));

   do
   {
		timeout.tv_sec  = 7;
		timeout.tv_usec = 0;

      memcpy(&working_set, &master_set, sizeof(master_set));

      printf("Waiting on select()...\n");
      rc = select(fd_max + 1, &working_set, NULL, NULL, &timeout);
      if (rc < 0)
      {
         perror("select() failed");
         break;
      }

      if (rc == 0)
      {
         printf("select() timed out.\n");
         continue;
      }

      desc_ready = rc;
      for (i=0; i <= fd_max  &&  desc_ready > 0; ++i)
      {
         /* Check to see if this descriptor is ready  */
         if (FD_ISSET(i, &working_set))
         {
            --desc_ready;

            if (i == fd_tcp)
            {
               rc = TCPAccept(i, &master_set, &fd_max);
               if(-1 == rc)
               {
                  close_conn = TRUE;
               }
            }

            else if(i == fd_udp)
            {
               close_conn = UDPSendAndRecive(fd_udp, &udp_addr);
               if (close_conn == TRUE)
               {
                  break;
               }
            }
         
            else if(i == STDIN_FILENO)
            {
               close_conn = end_server = Stdin(buffer);
            }
            else if(i == fd_broadcast)
            {
               close_conn = UDPSendAndRecive(i, &broadcast_addr);
               if(close_conn == TRUE)
               {
                  break;
               }
            } 
            
            else /* This is TCP */
            {
               close_conn = FALSE;

               while(close_conn == FALSE)
               {
                  close_conn = TCPSendAndRecive(i);
               }
            }
               /*************************************************/
               /*                  clean up                     */ 
               /*************************************************/
            if (close_conn)
            {
               close(i);
               FD_CLR(i, &master_set);
               if (i == fd_max)
               {
                  while (FD_ISSET(fd_max, &master_set) == FALSE)
                     fd_max -= 1;
               }
            }
         } /* End of if (FD_ISSET(i, &working_set)) */
      } /* End of loop through selectable descriptors */

   } while (end_server == FALSE);

   /*************************************************************/
   /* Clean up all of the sockets that are open                 */
   /*************************************************************/
   for (i=0; i <= fd_max; ++i)
   {
      if (FD_ISSET(i, &master_set))
         close(i);
   }

   return 0;
}