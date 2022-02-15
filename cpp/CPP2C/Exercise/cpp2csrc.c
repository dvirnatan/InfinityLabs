#include <stdio.h> /* printf() */
#include <stdlib.h> /* malloc() free() */

static int s_count = 0;

/****************Public Transport *****************/

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
	this->m_license_plate = ++s_count;
	printf("PublicTransport::Ctor()%d\n", this->m_license_plate);
	return *this;
}

void PublicDtor(PublicTrasport *const this)
{
	--s_count;
	printf("PublicTransport::Dtor()%d\n", this->m_license_plate);
}

PublicTrasport PublicCCtor(PublicTrasport *const this ,const PublicTrasport *const other)
{
	(void)other;
	this->m_license_plate = ++s_count;
	this->vptr = &PublicVtble;
	printf("PublicTransport::CCtor() %d\n", this->m_license_plate);
	return *this;
}

void PublicDisplay(PublicTrasport *const this)
{
	printf("PublicTransport::display(): %d\n", this->m_license_plate);
}

int get_ID(PublicTrasport *const this)
{
	return this->m_license_plate;
}

static void print_count()
{
	printf("s_count: %d\n", s_count);
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
	const vtable_minibus *vptr;
	struct PublicTrasport public_obj;
	int m_numSeats;
};

Minibus MinibusCtor(Minibus *const this)
{
	PublicCtor(&this->public_obj);
	printf("Minibus::Ctor()\n");
	this->vptr = &MinibusVtble;
	this->m_numSeats = 20;
	return *this;
}

Minibus MinibusCCtor(Minibus *const this, Minibus *const other)
{
	PublicCCtor(&this->public_obj, &other->public_obj);
	printf("Minibus::CCtor()\n");
	this->m_numSeats = other->m_numSeats;
	this->vptr = other->vptr;
	return *this;
}

void MinibusDtor(Minibus *const this)
{
	printf("Minibus::Dtor()\n");
	PublicDtor(&this->public_obj);
}

void MinibusWash(Minibus *const this, int minutes)
{
	printf("Minibus::wash(%d) ID:%d\n", minutes, get_ID(&this->public_obj));
}

void MinibusDisplay(Minibus *const this)
{
	printf("Minibus::display() ID:%d", get_ID(&this->public_obj));
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
	const vtable_taxi *vptr;
	PublicTrasport public_obj;
};

Taxi TaxiCtor(Taxi *const this)
{
	PublicCtor(&this->public_obj);
	printf("Taxi::Ctor()\n");
	this->vptr = &TaxiVtble; 
	return *this;
}

Taxi TaxiCCtor(Taxi *const this, Taxi *const other)
{
	this->vptr = &TaxiVtble;
	PublicCCtor(&this->public_obj, &other->public_obj);
	printf("Taxi::CCtor()\n");
	return *this;
}

void TaxiDtor(Taxi *const this)
{
	printf("Taxi::Dtor()\n");	
	PublicDtor(&this->public_obj);
}

void TaxiDisplay(Taxi *const this)
{
	printf("Taxi::display() ID:%d\n", get_ID(&this->public_obj));
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
	const vtable_special_taxi *vptr;
	Taxi taxi_obj;
};

SpecialTaxi SpecialTaxiCtor(SpecialTaxi *const this)
{
	TaxiCtor(&this->taxi_obj);
	printf("SpecialTaxi::Ctor()\n");
	this->vptr = &SpecialTaxiVtble;
	return *this;
}

SpecialTaxi SpecialTaxiCCtor(SpecialTaxi *const this,SpecialTaxi *const other)
{
	TaxiCCtor(&this->taxi_obj, &other->taxi_obj);
	printf("SpecialTaxi::CCtor()\n");
	return *this;
}

void SpecialTaxiDtor(SpecialTaxi *const this)
{
	printf("SpecialTaxi::Dtor()\n");	
	TaxiDtor(&this->taxi_obj);
}

void SpecialTaxiDisplay(SpecialTaxi *const this)
{
	printf("SpecialTaxi::display() ID:%d\n", get_ID(&this->taxi_obj.public_obj));
}

/**************Free Func****************/

void print_info_display(PublicTrasport *const this)
{
	this->vptr->Display(this);
}

void print_info_count()
{
	print_count();
}

void print_info_wash(Minibus *const this)
{
	this->vptr->Wash(this, 3);
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

int max_func(int t1, int t2)
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
	const vtable_public_convoy *vptr;
	PublicTrasport *m_ptr1;
	PublicTrasport *m_ptr2;
	Minibus m_m;
	Taxi m_t;
};

PublicConvoy PublicConvoyCtor(PublicConvoy *const this)
{
	this->vptr = &PublicConvoyVtble;
	this->m_ptr1 = malloc(sizeof(Minibus));
	PublicCtor(&this->public_transport_obj);
	MinibusCtor((Minibus*)this->m_ptr1);
	this->m_ptr2 = malloc(sizeof(Taxi));
	TaxiCtor((Taxi*)this->m_ptr2);
	MinibusCtor(&this->m_m);
	TaxiCtor(&this->m_t);

	return *this;
}

PublicConvoy PublicConvoyCCtor(PublicConvoy *const this, PublicConvoy *const other)
{
	this->vptr = &PublicConvoyVtble;
	PublicCCtor(&this->public_transport_obj, &other->public_transport_obj);
	this->m_ptr1 = malloc(sizeof(Minibus));
	this->m_ptr2 = malloc(sizeof(Taxi));
	MinibusCtor((Minibus*)this->m_ptr1);
	TaxiCtor((Taxi*)this->m_ptr2);
	MinibusCCtor(&this->m_m, &other->m_m);
	TaxiCCtor(&this->m_t, &other->m_t);

	return *this;
}

void PublicConvoyDtor(PublicConvoy *const this)
{
	this->m_ptr1->vptr->Dtor(this->m_ptr1);
	this->m_ptr2->vptr->Dtor(this->m_ptr2);
	this->m_t.vptr->Dtor(&this->m_t);
	this->m_m.vptr->Dtor(&this->m_m);
	this->public_transport_obj.vptr->Dtor(&this->public_transport_obj);
}

void PublicConvoyDisplay(PublicConvoy *const this)
{
	this->m_ptr1->vptr->Display(this->m_ptr1);
	this->m_ptr2->vptr->Display(this->m_ptr2);
	this->m_m.vptr->Display(&this->m_m);
	this->m_t.vptr->Display(&this->m_t);
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
		arr2[i].vptr->Display(&arr2[i]);
	}
	
	print_info_display(&arr2[0]);
	print_count();
	Minibus m2;
	MinibusCtor(&m2);
	print_count();

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

	printf("%d\n",max_func(1, 2));
	printf("%d\n",max_func(1, 2));

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
	ts1->vptr->Display(ts1);
	ts2->vptr->Display(ts2);
	PublicConvoyDtor(ts1);
	free(ts1);
	ts2->vptr->Display(ts2);
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
