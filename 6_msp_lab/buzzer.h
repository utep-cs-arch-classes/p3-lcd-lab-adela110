#ifndef buzzer_included
#define buzzer_included

#define C3 1300
#define CSHARP3 1390
#define D3 1470
#define DSHARP3 1560
#define E3 1650
#define F3 1750
#define FSHARP3 1850
#define G3 1960
#define GSHARP3 2080
#define A3 2200
#define ASHARP3 2330
#define B3 2470
#define C4 2620

void buzzer_init();
void buzzer_set_period(short cycles);

#endif // included
