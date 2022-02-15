#include <stdio.h> /* printf() */
#include <stdlib.h> /* malloc() free() */


/****************Public Transport *****************/
static int public_transport_count = 0;

typedef struct PublicTrasport PublicTrasport;

typedef struct 
{
	void (*const Dtor)(PublicTrasport *const);
	void (*const Display)(PublicTrasport *const);
}vtable_public_transport;

void PublicDisplay(PublicTrasport *const this);
void PublicDtor(PublicTrasport *const this);

static const vtable_public_transport PublicVtble = 
{
	&PublicDtor ,
	&PublicDisplay
};

struct PublicTrasport
{
	const vtable_public_transport *vptr;
	int m_license_plate;
};

/****************Public Transport functions*****************/

PublicTrasport PublicCtor(PublicTrasport *const this)
{
	this->vptr = &PublicVtble;
	this->m_license_plate = ++public_transport_count;
	printf("PublicTransport::Ctor()%d\n", this->m_license_plate);
	return *this;
}

void PublicDtor(PublicTrasport *const this)
{
	this->vptr = &PublicVtble;
	--public_transport_count;
	printf("PublicTransport::Dtor()%d\n", this->m_license_plate);
}

PublicTrasport PublicCCtor(PublicTrasport *const this ,const PublicTrasport *const other)
{
	(void)other;
	this->vptr = &PublicVtble;
	this->m_license_plate = ++public_transport_count;
	printf("PublicTransport::CCtor() %d\n", this->m_license_plate);
	return *this;
}

void PublicDisplay(PublicTrasport *const this)
{
	printf("PublicTransport::display(): %d\n", this->m_license_plate);
}

int PublicGet_ID(PublicTrasport *const this)
{
	return this->m_license_plate;
}

static void PublicPrint_count()
{
	printf("s_count: %d\n", public_transport_count);
}

/*********************Minibus*********************/
typedef struct Minibus Minibus;
typedef struct 
{
	void (*const Dtor)(Minibus *const);
	void (*const Display)(Minibus *const);
	void (*const Wash)(Minibus *const, int);
}vtable_minibus;

void MinibusDtor (Minibus *const this);
void MinibusDisplay(Minibus *const this);
void MinibusWash (Minibus *const this, int minutes);

static const vtable_minibus MinibusVtble = 
{
	&MinibusDtor,
	&MinibusDisplay,
	&MinibusWash
};

struct Minibus
{
	struct PublicTrasport public_obj;
	int m_numSeats;
};

Minibus MinibusCtor(Minibus *const this)
{
	PublicCtor(&this->public_obj);
	this->public_obj.vptr = (vtable_public_transport*)&MinibusVtble;

	this->m_numSeats = 20;
	printf("Minibus::Ctor()\n");

	return *this;
}

Minibus MinibusCCtor(Minibus *const this, Minibus *const other)
{
	PublicCCtor(&this->public_obj, &other->public_obj);
	this->public_obj.vptr = (vtable_public_transport*)&MinibusVtble;

	printf("Minibus::CCtor()\n");
	this->m_numSeats = other->m_numSeats;

	return *this;
}

void MinibusDtor(Minibus *const this)
{
	this->public_obj.vptr = (vtable_public_transport*)&MinibusVtble;

	printf("Minibus::Dtor()\n");
	PublicDtor(&this->public_obj);
}

void MinibusWash(Minibus *const this, int minutes)
{
	printf("Minibus::wash(%d) ID:%d\n", minutes, PublicGet_ID(&this->public_obj));
}

void MinibusDisplay(Minibus *const this)
{
	printf("Minibus::display() ID:%d", PublicGet_ID(&this->public_obj));
	printf(" num seats:%d\n", this->m_numSeats);
}
/********************Taxi********************/
typedef struct Taxi Taxi;

typedef struct 
{
	void (*const Dtor)(Taxi *const);
	void (*const Display)(Taxi *const);
}vtable_taxi;

void TaxiDtor(Taxi *const this);
void TaxiDisplay(Taxi *const this);

static const vtable_taxi TaxiVtble = 
{
	&TaxiDtor,
	&TaxiDisplay
};

struct Taxi
{
	PublicTrasport public_obj;
};

Taxi TaxiCtor(Taxi *const this)
{
	PublicCtor(&this->public_obj);
	this->public_obj.vptr = (vtable_public_transport*)&TaxiVtble; 

	printf("Taxi::Ctor()\n");

	return *this;
}

Taxi TaxiCCtor(Taxi *const this, Taxi *const other)
{
	PublicCCtor(&this->public_obj, &other->public_obj);
	this->public_obj.vptr = (vtable_public_transport*)&TaxiVtble; 

	printf("Taxi::CCtor()\n");

	return *this;
}

void TaxiDtor(Taxi *const this)
{
	this->public_obj.vptr = (vtable_public_transport*)&TaxiVtble; 

	printf("Taxi::Dtor()\n");	
	PublicDtor(&this->public_obj);
}

void TaxiDisplay(Taxi *const this)
{
	printf("Taxi::display() ID:%d\n", PublicGet_ID(&this->public_obj));
}

/****************SpecialTaxi**************/

typedef struct SpecialTaxi SpecialTaxi;

typedef struct 
{
	void (*const Dtor)(SpecialTaxi *const);
	void (*const Display)(SpecialTaxi *const);
}vtable_special_taxi;

void SpecialTaxiDtor(SpecialTaxi *const this);
void SpecialTaxiDisplay(SpecialTaxi *const this);

static const vtable_special_taxi SpecialTaxiVtble = 
{
	&SpecialTaxiDtor,
	&SpecialTaxiDisplay
};

struct SpecialTaxi
{
	Taxi taxi_obj;
};

SpecialTaxi SpecialTaxiCtor(SpecialTaxi *const this)
{
	TaxiCtor(&this->taxi_obj);
	this->taxi_obj.public_obj.vptr = (vtable_public_transport*)&SpecialTaxiVtble;

	printf("SpecialTaxi::Ctor()\n");

	return *this;
}

SpecialTaxi SpecialTaxiCCtor(SpecialTaxi *const this,SpecialTaxi *const other)
{
	TaxiCCtor(&this->taxi_obj, &other->taxi_obj);
	this->taxi_obj.public_obj.vptr = (vtable_public_transport*)&SpecialTaxiVtble;

	printf("SpecialTaxi::CCtor()\n");

	return *this;
}

void SpecialTaxiDtor(SpecialTaxi *const this)
{
	this->taxi_obj.public_obj.vptr = (vtable_public_transport*)&SpecialTaxiVtble;

	printf("SpecialTaxi::Dtor()\n");

	TaxiDtor(&this->taxi_obj);
}

void SpecialTaxiDisplay(SpecialTaxi *const this)
{
	printf("SpecialTaxi::display() ID:%d\n", PublicGet_ID(&this->taxi_obj.public_obj));
}

/**************Free Func****************/

void PublicTransportDisplay(PublicTrasport *const this)
{
	this->vptr->Display(this);
}

void print_info_count()
{
	PublicPrint_count();
}

void print_info_wash(Minibus *const this)
{
	((vtable_minibus*)this->public_obj.vptr)->Wash(this, 3);
}

PublicTrasport print_info_int(int i)
{
	(void)i;
	Minibus ret;
	MinibusCtor(&ret);
	printf("print_info(int i)\n");
	MinibusDisplay(&ret);
	PublicTrasport temp;
	PublicCCtor(&temp, &ret.public_obj);
	MinibusDtor(&ret);
	return temp;
}

int max_func_int(int t1, int t2)
{
	return ((t1 > t2) ? t1 : t2);
}
/***************PublicConvoy*************/

typedef struct PublicConvoy PublicConvoy;

typedef struct 
{
	void (*const Dtor)(PublicConvoy *const);
	void (*const Display)(PublicConvoy *const);
}vtable_public_convoy;

void PublicConvoyDtor(PublicConvoy *const this);
void PublicConvoyDisplay(PublicConvoy *const this);

static const vtable_public_convoy PublicConvoyVtble = 
{
	&PublicConvoyDtor,
	&PublicConvoyDisplay
};

struct PublicConvoy
{
	PublicTrasport public_transport_obj;
	PublicTrasport *m_ptr1;
	PublicTrasport *m_ptr2;
	Minibus m_m;
	Taxi m_t;
};

PublicConvoy PublicConvoyCtor(PublicConvoy *const this)
{
	PublicCtor(&this->public_transport_obj);
	this->public_transport_obj.vptr = (vtable_public_transport*)&PublicConvoyVtble;

	this->m_ptr1 = malloc(sizeof(Minibus));
	MinibusCtor((Minibus*)this->m_ptr1);

	this->m_ptr2 = malloc(sizeof(Taxi));
	TaxiCtor((Taxi*)this->m_ptr2);

	MinibusCtor(&this->m_m);
	TaxiCtor(&this->m_t);

	return *this;
}

PublicConvoy PublicConvoyCCtor(PublicConvoy *const this, PublicConvoy *const other)
{
	PublicCCtor(&this->public_transport_obj, &other->public_transport_obj);
	this->public_transport_obj.vptr = (vtable_public_transport*)&PublicConvoyVtble;

	this->m_ptr1 = malloc(sizeof(Minibus));
	MinibusCtor((Minibus*)this->m_ptr1);

	this->m_ptr2 = malloc(sizeof(Taxi));
	TaxiCtor((Taxi*)this->m_ptr2);

	MinibusCCtor(&this->m_m, &other->m_m);
	TaxiCCtor(&this->m_t, &other->m_t);

	return *this;
}

void PublicConvoyDtor(PublicConvoy *const this)
{
	this->public_transport_obj.vptr = (vtable_public_transport*)&PublicConvoyVtble;

	this->m_ptr1->vptr->Dtor(this->m_ptr1);
	free(this->m_ptr1);

	this->m_ptr2->vptr->Dtor(this->m_ptr2);
	free(this->m_ptr2);

	TaxiDtor(&this->m_t);
	MinibusDtor(&this->m_m);
	PublicDtor(&this->public_transport_obj);
}

void PublicConvoyDisplay(PublicConvoy *const this)
{
	this->m_ptr1->vptr->Display(this->m_ptr1);
	this->m_ptr2->vptr->Display(this->m_ptr2);
	MinibusDisplay(&this->m_m);
	TaxiDisplay(&this->m_t);
}


/***************Main******************/

int main()
{
 	Minibus m;
	MinibusCtor(&m);
	print_info_wash(&m); 
	
	PublicTrasport temp;
	temp = print_info_int(3);
	temp.vptr->Display(&temp);
	PublicDtor(&temp);
	
	PublicTrasport *const array[3] = 
	{
		malloc(sizeof(Minibus)),
		malloc(sizeof(Taxi)),
		malloc(sizeof(Minibus))
	};
	
	MinibusCtor((Minibus *const)array[0]);
	TaxiCtor((Taxi *const)array[1]);
	MinibusCtor((Minibus *const)array[2]);

	for(int i = 0; i < 3; ++i)
	{
		array[i]->vptr->Display(array[i]);
	}

	for(int i = 0; i < 3; ++i)
	{
		array[i]->vptr->Dtor(array[i]);
		free(array[i]);
	}
	PublicTrasport arr2[3];
	Minibus mm;
	MinibusCtor(&mm);
	PublicCCtor(&arr2[0] , &m.public_obj);
	MinibusDtor(&mm);

	Taxi t;
	TaxiCtor(&t);
	PublicCCtor(&arr2[1], &t.public_obj);
	TaxiDtor(&t);

	PublicCtor(&arr2[2]);
	
	for(int i = 0; i < 3; ++i)
	{
		PublicTransportDisplay(&arr2[i]);
	}
	
	PublicTransportDisplay(&arr2[0]);
	PublicPrint_count();
	Minibus m2;
	MinibusCtor(&m2);
	PublicPrint_count();

	Minibus arr3[4];
	for(int i = 0; i < 4; ++i)
	{
		MinibusCtor(&arr3[i]);
	}

	Taxi *arr4 = malloc(sizeof(Taxi) * 4);
	for (int i = 0; i < 4; ++i)
	{
		TaxiCtor(&arr4[i]);
	}
	for(int i = 3; i >=0; --i)
	{
		TaxiDtor(&arr4[i]);
	}
	free(arr4);

	printf("%d\n",max_func_int(1, 2));
	printf("%d\n",max_func_int(1, 2.0f));

	SpecialTaxi st;
	SpecialTaxiCtor(&st);
	Taxi tempp;
	TaxiCCtor(&tempp, &st.taxi_obj);
	TaxiDisplay(&tempp);
	TaxiDtor(&tempp);
	PublicConvoy *ts1 = malloc(sizeof(PublicConvoy));
	PublicConvoyCtor(ts1);
	PublicConvoy *ts2 = malloc(sizeof(PublicConvoy));
	PublicConvoyCCtor(ts2, ts1);
	ts1->public_transport_obj.vptr->Display((PublicTrasport* const)ts1);
	ts2->public_transport_obj.vptr->Display((PublicTrasport* const)ts2);
	PublicConvoyDtor(ts1);
	free(ts1);
/* 	printf("#####################################333\n"); */
	ts2->public_transport_obj.vptr->Display((PublicTrasport* const)ts2);
	PublicConvoyDtor(ts2);
	free(ts2);

	SpecialTaxiDtor(&st);

	for(int i = 3; i >= 0; --i)
	{
		MinibusDtor(&arr3[i]);
	}

	MinibusDtor(&m2);
	PublicDtor(&arr2[2]);
	PublicDtor(&arr2[1]);
	PublicDtor(&arr2[0]);
	MinibusDtor(&m); 
	return 0;
}
