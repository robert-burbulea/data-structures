#include <stdio.h>
#include <string.h>

static void tire_pressure_status(void* data);
static void tire_temperature_status(void* data);
static void tire_wear_level_status(void* data);
static void tire_performance_score(void* data);
static void pmu_compute_power(void* data);
static void pmu_regenerate_energy(void* data);
static void pmu_get_energy_usage(void* data);
static void pmu_is_battery_healthy(void* data);
void get_operations(void **operations);
