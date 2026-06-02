#pragma once
typedef bitset<1> bit;
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
	//IRON,
	//HEATSUPERCONDUCTOR,
	//DISABLED_HSC,
	//COPPER,
	ANTIGRAVITY_PLATE,
	BEDROCK,
	//ICE,
	//PLUTONIUM,
	//BREAD_PLURONIUM,

	////liqids
	//WATER,
	//MOLTEN_STONE,
	//MOLTEN_GLASS,
	//MOLTEN_ORE,
	//MOLTEN_SLAG,
	//MOLTEN_IRON,
	//MOLTEN_COPPER,

	////bombs
	//TNT,
	//TERMITE,
	//MEGATNT,

	////mechanisms
	//GANTRY_SHAFT,
	//GANTRY_CARRIAGE,
	//VALVE,
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
	//particle
	COUNT,
	DIRECTION,
};
enum variablef {
	//bacis
	TEMPRATURE,
};

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
			break;
		}
		break;
	case ANTIGRAVITYSAND:
		switch (selector)
		{
		case TYPE:
			return BASICMAT;
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
	default:
		cout << "ERROR AT TYPE FINDER";
		break;
	}
}

float constf(matreals type, paramiterf selector) {

}

bit constb(matreals type, paramiterb selector) {

}
