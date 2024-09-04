#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "operations.h"

power_management_unit *Init_power_management_unit(FILE *fin, FILE *fout) {
	power_management_unit *pmu = (power_management_unit *) malloc(sizeof(power_management_unit));
	if(!pmu) {
		fprintf(fout, "Could not allocate memory");
	}
			fscanf(fin, "%f", &pmu->power_consumption);
			fscanf(fin, "%f", &pmu->current);
			fscanf(fin, "%f", &pmu->voltage);
			fscanf(fin, "%d", &pmu->energy_regen);
			fscanf(fin, "%d", &pmu->energy_storage);
	return pmu;
}

void Print_power_management_unit(power_management_unit *pmu, FILE *fout) {
	fprintf(fout, "Power Management Unit\n");
	fprintf(fout, "Voltage: %.2f\n", pmu->voltage);
	fprintf(fout, "Current: %.2f\n", pmu->current);
	fprintf(fout, "Power Consumption: %.2f\n", pmu->power_consumption);
	fprintf(fout, "Energy Regen: %d%\n", pmu->energy_regen);
	fprintf(fout, "Energy Storage: %d%\n", pmu->energy_storage);
}

tire_sensor *Init_tire_sensor(FILE *fin, FILE *fout) {
	tire_sensor *ts = (tire_sensor *) malloc(sizeof(tire_sensor));
    if(!ts) {
        fprintf(fout, "Could not allocate memory");
    }
	    fscanf(fin, "%f", &ts->pressure);
		fscanf(fin, "%f", &ts->temperature);
		fscanf(fin, "%d", &ts->wear_level);
		fscanf(fin, "%d", &ts->performace_score);
            
    return ts;
}

void Print_tire_sensor(tire_sensor *ts, FILE *fout) {
	fprintf(fout, "Tire Sensor\n");
	fprintf(fout, "Pressure: %.2f\n", ts->pressure);
    fprintf(fout, "Temperature: %.2f\n", ts->temperature);
    fprintf(fout, "Wear Level: %d%\n", ts->wear_level);
	if(ts->performace_score == 0) {
		fprintf(fout, "Performace Score: Not Calculated\n");
	} else {
    	fprintf(fout, "Performace Score: %d\n", ts->performace_score);
	}
}

sensor *Init_sensor(FILE *fin, FILE *fout) {
	power_management_unit *pmu;
	tire_sensor *ts;
	sensor *s = (sensor *) malloc(sizeof(sensor));
	if(!s) {
        fprintf(fout, "Could not allocate memory");
    }

	int sensor_type;
	fscanf(fin, "%d", &sensor_type);
		if (sensor_type == 1) { // PMU sensor
		    s->sensor_type = PMU;
		    pmu = Init_power_management_unit(fin, fout);
			s->sensor_data = pmu;
		} else if (sensor_type == 0) { //Tire Sensor
		    s->sensor_type = TIRE;
			ts = Init_tire_sensor(fin, fout);
			s->sensor_data = ts;
		} else {
			fprintf(fout, "Unknown sensor type");
		}
	
	int nr_operations;
	fscanf(fin, "%d", &nr_operations);
	s->nr_operations = nr_operations;
	s->operations_idxs = (int*) malloc(nr_operations * sizeof(int));
	if (!s->operations_idxs) {
		fprintf(fout, "Could not allocate memory");
    }
	for (int i = 0; i < nr_operations; i++) {
		int operation;
		fscanf(fin, "%d", &operation);
		s->operations_idxs[i] = operation;
	}
	return s;
}

void Print_sensor(sensor *s, FILE *fout) {
	if (s->sensor_type == 0) {
		Print_tire_sensor(s->sensor_data, fout);
	} else {
		Print_power_management_unit(s->sensor_data, fout);
	}

}

sensor **Init_sensor_vector(int number_of_sensors, FILE *fin, FILE *fout) {
	sensor **sensors = (sensor **) malloc(number_of_sensors * sizeof(sensor *));
	if(!sensors) {
        fprintf(fout, "Could not allocate memory");
    }
	for (int i = 0; i < number_of_sensors; i++) {
        sensors[i] = Init_sensor(fin, fout);
    }
	return sensors;
}

void Print_sensor_vector(sensor **sensors, int index, FILE *fout) {
	Print_sensor(sensors[index], fout);
}

void Print_sensor_vector_complex(sensor **sensors, int number_of_sensors, FILE *fout) {
	int pmu_index, ts_index, i;

	//first print all PMUs
	for (i = 0; i < number_of_sensors; i++) {
        if (sensors[i]->sensor_type == PMU) {
            // Print_power_management_unit(sensors[i]->sensor_data);
			Print_sensor(sensors[i], fout);
        }
    }

    //then print all Tires
    for (i = 0; i < number_of_sensors; i++) {
        if (sensors[i]->sensor_type == TIRE) {
            // Print_tire_sensor(sensors[i]->sensor_data);
			Print_sensor(sensors[i], fout);
        }
    }
}


void Analyze(sensor *sensor) {
	void **operations = (void **)malloc(8 * sizeof(void *));
	get_operations(operations);
	for (int i = 0; i < sensor->nr_operations; i++) {
		int operation_index = sensor->operations_idxs[i];
		void (*func_ptr)(void*) = (void (*)(void*))operations[operation_index];
        func_ptr(sensor->sensor_data);
	}

}

int verify_sensor(sensor *sensor) {
	if(sensor->sensor_type == TIRE) {
		tire_sensor *ts = sensor->sensor_data;
		if(ts->pressure < 19 || ts->pressure > 28) return 0;
		if(ts->temperature < 0 || ts->temperature > 120) return 0;
		if(ts->wear_level < 0 || ts->wear_level > 100) return 0;
		return 1;
	}

	power_management_unit *pmu = sensor->sensor_data;
	if(pmu->voltage < 10 || pmu->voltage > 20) return 0;
	if(pmu->current < -100 || pmu->current > 100) return 0;
	if(pmu->power_consumption < 0 || pmu->power_consumption > 1000) return 0;
	if(pmu->energy_regen < 0 || pmu->energy_regen > 100) return 0;
	if(pmu->energy_storage < 0 || pmu->energy_storage > 100) return 0;
	return 1;
}


//TODO: test
//TODO: free sensor after "deletion"
void Clear(sensor **sensors, int number_of_sensors) {
	int i = 0;
	while(i < number_of_sensors) {
		// if we have to delete the sensor
		if(verify_sensor(sensors[i]) == 0) {
			for (int j = i + 1; j < number_of_sensors; j++) {
				sensors[j - 1] = sensors[j];
			}
			number_of_sensors--;
		} else {
			i++;
		}
	}
}

//TODO: test
void Exit(sensor **sensors, int number_of_sensors) {
	for (int i = 0; i < number_of_sensors; i++) {
		free(sensors[i]->sensor_data);
		free(sensors[i]->operations_idxs);
		free(sensors[i]);
	}
	free(sensors);
}

void read_commands(sensor **sensors, int number_of_sensors, FILE *fout) {
	char *line, *command, *index_pointer;
	int index;
	command = (char *)malloc(sizeof(char) * 30);



	while(1) {
		scanf("%s", command);
		
		if (strcmp(command, "print") == 0) {
			scanf("%d", &index);
			// fprintf(fout, "%s %d\n", command, index);
			Print_sensor_vector(sensors, index, fout);

		} else if(strcmp(command, "analyze") == 0) {
			scanf("%d", &index);
			// fprintf(fout, "%s %d\n", command, index);
		} else if(strcmp(command, "clear") == 0) {
			// fprintf(fout, "%s\n", command);

		} else if(strcmp(command, "exit") == 0) {
			// fprintf(fout, "%s\n", command);
			Exit(sensors, number_of_sensors);
			break;
		}
	}

}


int main(int argc, char const *argv[])
{
	int number_of_sensors; 
	sensor **sensors;

	FILE *fin, *fout;
	fin = fopen(argv[1], "r");
	fout = fopen("file.out", "w");

	fscanf(fin, "%d", &number_of_sensors);
	sensors = Init_sensor_vector(number_of_sensors, fin, fout);
	read_commands(sensors, number_of_sensors, fout);


	char *line = (char *) malloc(1024 * sizeof(char));
	while (fgets(line, sizeof(line), fout) != NULL) {
    printf("%s", line);
  }

	
	


	

	return 0;
}
