#pragma once
#include <bit>
#include <bitset>
#include <iostream>
#include "BMPreader.h"

using namespace std;
typedef bool bit;
//з матеріалов не видаляти
enum matreals {
	VOIDM,

	////gases
	//AIR,
	//STEAM,
	//KRYPTON,

	//sands
	SAND,
	ANTIGRAVITYSAND,
	//GRAVEL,
	//DUST,
	//BLACKHOLE_DUST,
	//PACKED_SAND,
	//WET_SAND,
	//IRON_ORE,

	////solids
	IRON,
	//HEATSUPERCONDUCTOR,
	//DISABLED_HSC,
	COPPER,
	ANTIGRAVITY_PLATE,
	BEDROCK,
	//ICE,
	//PLUTONIUM,
	//BREAD_PLURONIUM,

	////liqids
	WATER,
	//MOLTEN_STONE,
	//MOLTEN_GLASS,
	//MOLTEN_ORE,
	//MOLTEN_SLAG,
	MOLTEN_IRON,
	MOLTEN_COPPER,

	////bombs
	//TNT,
	//TERMITE,
	//MEGATNT,

	////mechanisms
	//GANTRY_SHAFT,
	//GANTRY_CARRIAGE,
	GATE,
	//PULSER,
	//CONDUCTBRIDGE,

	////particles
	//NEUTRON,
};
enum classes {
	VOIDC,
	BASICMAT,
	COUNDUCTOR,
	PARTICLE,
};
enum paramiterb {
	IS_MOVABLE,
	IS_SIMPLEFALLABLE,
	IS_SIMPLEFLOATABLE,
};
enum paramiteri {
	TYPE,
	DENSITY,
	MELT_TYPE,
	SOLID_TYPE,
};
enum paramiterf {
	THERMAL_CONDUCIVITY,
	MELT_TEMPRATURE,
	SOLID_TEMPRATURE,
};
enum variableb {
	//conductor
	POWER,
	ELCOLDOWN,
};
enum variablei {
	TYPEV,
	//particle
	COUNT,
	DIRECTION,
};
enum variablef {
	//bacis

	TEMPRATURE,
};
union Uv {
	variableb bv;
	variablei iv;
	variablef fv;
};

vector<pair<Uv, unsigned char>> paramiterclasses(classes a) {
	vector<pair<Uv, unsigned char>> b;
	switch (a)
	{
	case VOIDC:
		for (int i = 0; i < 1; i++) {
			b.push_back({});
		}
		b[0].first.iv = TYPEV;
		b[0].second = 1;
		break;
	case BASICMAT:
		for (int i = 0; i < 2; i++) {
			b.push_back({});
		}
		b[0].first.iv = TYPEV;
		b[0].second = 1;
		b[1].first.fv = TEMPRATURE;
		b[1].second = 2;
		break;
	case COUNDUCTOR:
		for (int i = 0; i < 4; i++) {
			b.push_back({});
		}
		b[0].first.iv = TYPEV;
		b[0].second = 1;
		b[1].first.fv = TEMPRATURE;
		b[1].second = 2;
		b[2].first.bv = POWER;
		b[2].second = 0;
		b[3].first.bv = ELCOLDOWN;
		b[3].second = 0;
		break;
	case PARTICLE:
		break;
	default:
		break;
	}
	return b;
}
int consti(matreals type, paramiteri selector) {
	switch (type)
	{
	case VOIDM:
		switch (selector)
		{
		case TYPE:
			return VOIDC;
			break;
		case DENSITY:
			return 0;
			break;
		default:
			return -1;
			break;
		}
		break;
	case SAND:
		switch (selector)
		{
		case TYPE:
			return BASICMAT;
			break;
		case DENSITY:
			return 10;
			break;
		case MELT_TYPE:
			return -1;
			break;
		case SOLID_TYPE:
			return -1;
			break;
		default:
			return -1;
			break;
		}
		break;
	case ANTIGRAVITYSAND:
		switch (selector)
		{
		case TYPE:
			return COUNDUCTOR;
			break;
		case DENSITY:
			return -10;
			break;
		case MELT_TYPE:
			return -1;
			break;
		case SOLID_TYPE:
			return -1;
			break;
		default:
			return -1;
			break;
		}
		break;
	case ANTIGRAVITY_PLATE:
		switch (selector)
		{
		case TYPE:
			return BASICMAT;
			break;
		case DENSITY:
			return 1000;
			break;
		case MELT_TYPE:
			return -1;
			break;
		case SOLID_TYPE:
			return -1;
			break;
		default:
			return -1;
			break;
		}
		break;
	case BEDROCK:
		switch (selector)
		{
		case TYPE:
			return BASICMAT;
			break;
		case DENSITY:
			return 1000000;
			break;
		default:
			return -1;
			break;
		}
		break;
	case WATER:
		switch (selector)
		{
		case TYPE:
			return BASICMAT;
			break;
		case DENSITY:
			return 5;
			break;
		case MELT_TYPE:
			return -1;
			break;
		case SOLID_TYPE:
			return -1;
			break;
		default:
			break;
		}
		break;
	case IRON:
		switch (selector)
		{
		case TYPE:
			return COUNDUCTOR;
			break;
		case DENSITY:
			return 40;
			break;
		case MELT_TYPE:
			return MOLTEN_IRON;
			//cout << 'a';
			break;
		case SOLID_TYPE:
			break;
		default:
			break;
		}
		break;
	case MOLTEN_IRON:
		switch (selector)
		{
		case TYPE:
			return BASICMAT;
			break;
		case DENSITY:
			return 20;
			break;
		case MELT_TYPE:
			return -1;
			break;
		case SOLID_TYPE:
			return IRON;
			break;
		default:
			break;
		}
	case COPPER:
		switch (selector)
		{
		case TYPE:
			return COUNDUCTOR;
			break;
		case DENSITY:
			break;
		case MELT_TYPE:
			return MOLTEN_COPPER;
			break;
		case SOLID_TYPE:
			break;
		default:
			break;
		}
	case MOLTEN_COPPER:
		switch (selector)
		{
		case TYPE:
			return BASICMAT;
			break;
		case DENSITY:
			return 19;
			break;
		case MELT_TYPE:
			return -1;
			break;
		case SOLID_TYPE:
			return COPPER;
			break;
		default:
			break;
		}
	case GATE:
		switch (selector)
		{
		case TYPE:
			return COUNDUCTOR;
			break;
		case DENSITY:
			return 100;
			break;
		case MELT_TYPE:
			return -1;
			break;
		case SOLID_TYPE:
			return -1;
			break;
		default:
			break;
		}
	default:
		if (selector != MELT_TYPE or selector != SOLID_TYPE)
			cout << "ERROR AT TYPE FINDER";
		break;
	}

	return -1;
}

float constf(matreals type, paramiterf selector) {
	switch (type)
	{
	case VOIDM:
		switch (selector)
		{
		case THERMAL_CONDUCIVITY:
			return 0.01;
			break;
		case MELT_TEMPRATURE:
			break;
		case SOLID_TEMPRATURE:
			break;
		default:
			break;
		}
		break;
	case SAND:
		break;
	case ANTIGRAVITYSAND:
		break;
	case ANTIGRAVITY_PLATE:
		break;
	case BEDROCK:
		break;
	case WATER:
		break;
	case IRON:
		switch (selector)
		{
		case THERMAL_CONDUCIVITY:
			return 0.25;
			break;
		case MELT_TEMPRATURE:
			return 2000;
			break;
		case SOLID_TEMPRATURE:
			break;
		default:
			break;
		}
	case MOLTEN_IRON:
		switch (selector)
		{
		case THERMAL_CONDUCIVITY:
			return 0.2;
			break;
		case MELT_TEMPRATURE:
			break;
		case SOLID_TEMPRATURE:
			break;
		default:
			break;
		}
	case COPPER:
		switch (selector)
		{
		case THERMAL_CONDUCIVITY:
			return 0.35;
			break;
		case MELT_TEMPRATURE:
			return 500;
			break;
		case SOLID_TEMPRATURE:
			break;
		default:
			break;
		}

	case MOLTEN_COPPER:
		switch (selector)
		{
		case THERMAL_CONDUCIVITY:
			return 0.35;
			break;
		case MELT_TEMPRATURE:
			break;
		case SOLID_TEMPRATURE:
			return 500;
			break;
		default:
			break;
		}
	case GATE:
		switch (selector)
		{
		case THERMAL_CONDUCIVITY:
			return 0.05;
			break;
		case MELT_TEMPRATURE:
			break;
		case SOLID_TEMPRATURE:
			break;
		default:
			break;
		}
	default:
		break;
	}

	return 0;
}

bool constb(matreals type, paramiterb selector) {
	switch (type)
	{
	case VOIDM:
		break;
	case SAND:
		switch (selector)
		{
		case IS_MOVABLE:
			break;
		case IS_SIMPLEFALLABLE:
			return true;
			break;
		default:
			break;
		}
		break;
	case ANTIGRAVITYSAND:
		break;
	case IRON:
		break;
	case ANTIGRAVITY_PLATE:
		break;
	case BEDROCK:
		break;
	case WATER:
		switch (selector)
		{
		case IS_MOVABLE:
			break;
		case IS_SIMPLEFLOATABLE:
			return true;
			break;
		case IS_SIMPLEFALLABLE:
			return true;
			break;
		default:
			break;
		}
		break;
	case MOLTEN_COPPER:
		switch (selector)
		{
		case IS_MOVABLE:
			break;
		case IS_SIMPLEFLOATABLE:
			return true;
			break;
		case IS_SIMPLEFALLABLE:
			return true;
			break;
		default:
			break;
		}
		break;
	case MOLTEN_IRON:
		switch (selector)
		{
		case IS_MOVABLE:
			break;
		case IS_SIMPLEFLOATABLE:
			return true;
			break;
		case IS_SIMPLEFALLABLE:
			return true;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return false;
}
enum updatesets {
	TERMAL,
	FALLING,
	FLOATING,
	ELECTRISITY,
	ELCOLDOWNS,
	GATECOOLDOWNSET,

	//new values here
	EVERYTHING,
	//values for non update uses
	GATEUPDATE,
	//new non update values here

	CLOSEGATE,
};


struct UPDATESETCOUNTclass {
	int count = 1;
	int count2 = 1;
	UPDATESETCOUNTclass() {
		for (int i = 0; i != CLOSEGATE; i++) {
			count++;
			if (i < EVERYTHING) {
				count2++;
			}
		}
	}
};

UPDATESETCOUNTclass UPDATESETCOUNT;


