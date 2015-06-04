#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int ARRAY_CAPACITY = 100;
const int INITIAL_CAPACITY = 10;

struct Vector {
	char **arr;
	int size;
	int capacity;
};

struct MapEntry {
	char *key;
	struct Vector *values;
	struct MapEntry *next;
};

struct HashMap {
	struct MapEntry **arr;
	int size;
};

struct Vector *constructVector() {
	struct Vector *vec = malloc(sizeof(struct Vector));
	vec->arr = malloc(sizeof(char *) * INITIAL_CAPACITY);
	vec->size = 0;
	vec->capacity = INITIAL_CAPACITY;
	return vec;
}


void push_back(struct Vector *vec, char *data) {
	if (vec->size >= vec->capacity) {
		char **temp = malloc(sizeof(char *) * vec->capacity * 2);
		memcpy(temp, vec->arr, sizeof(char *) * vec->capacity);
		free(vec->arr);
		vec->arr = temp;
		vec->capacity *= 2;
	}
	vec->arr[vec->size++] = data;
}

struct MapEntry *constructMapEntry(char *key, char *value) {
	if (key == NULL || value == NULL) {
		printf("Error. Null argument.");
		exit(1);
	}
	struct MapEntry *entry = malloc(sizeof(struct MapEntry));
	entry->key = key;
	entry->values = constructVector();
	push_back(entry->values, value);
	entry->next = NULL;
	return entry;
}

struct HashMap *constructHashMap() {
	struct HashMap *map = malloc(sizeof(struct HashMap));
	map->arr = malloc(sizeof(struct MapEntry *) * ARRAY_CAPACITY);
	map->size = 0;
	return map;
}

void deconstructVector(struct Vector *vec) {
	free(vec->arr);
	free(vec);
}

void deconstructMapEntry(struct MapEntry *entry) {
	deconstructVector(entry->values);
	free(entry);
}

void deconstructHashMap(struct HashMap *map) {
	int i;
	for (i = 0; i < ARRAY_CAPACITY; i += 1) {
		struct MapEntry *entry = map->arr[i];
		while (entry != NULL) {
			struct MapEntry *temp = entry;
			entry = entry->next;
			deconstructMapEntry(temp);
		}
	}
	free(map->arr);
	free(map);
}

int hashCode(char *key) {
	int result = 17;
	int i;
	for (i = 0; i < strlen(key); i += 1) {
		result = result * 31 + key[i];
	}
	return result;
}

void put(struct HashMap *map, char *key, char *value) {
	if (map == NULL || key == NULL || value == NULL) {
		printf("Error. Null argument.");
		exit(1);
	}
	int index = hashCode(key) % ARRAY_CAPACITY;
	struct MapEntry *entry = map->arr[index];
	while (entry != NULL) {
		if (strcmp(key, entry->key) == 0) {
			push_back(entry->values, value);
			map->size += 1;
			return;
		}
		entry = entry->next;
	}
	entry = constructMapEntry(key, value);
	entry->next = map->arr[index];
	map->arr[index] = entry;
	map->size += 1;
}

struct Vector *removeEntry(struct HashMap *map, char *key) {
	if (map == NULL || key == NULL) {
		printf("Error. Null argument.");
		exit(1);
	}
	int index = hashCode(key) % ARRAY_CAPACITY;
	struct MapEntry *entry = map->arr[index];
	if (entry == NULL) {
		return NULL;
	}
	if (strcmp(key, entry->key) == 0) {
		map->arr[index] = NULL;
		struct Vector *values = entry->values;
		free(entry);
		map->size -= values->size;
		return values;
	}
	while (entry->next != NULL) {
		if (strcmp(key, entry->next->key) == 0) {
			struct MapEntry *temp = entry->next;
			entry->next = temp->next;
			struct Vector *values = temp->values;
			free(temp);
			map->size -= values->size;
			return values;
		}
		entry = entry->next;
	}
	return NULL;
}

int isEmpty(struct HashMap *map) {
	if (map->size == 0) {
		return 1;
	}
	return 0;
}

struct Vector *get(struct HashMap *map, char *key) {
	if (map == NULL || key == NULL) {
		printf("Error. Null argument.");
		exit(1);
	}
	int index = hashCode(key) % ARRAY_CAPACITY;
	struct MapEntry *entry = map->arr[index];
	while (entry != NULL) {
		if (strcmp(key, entry->key) == 0) {
			return entry->values;
		}
		entry = entry->next;
	}
	return NULL;
}

int containsKey(struct HashMap *map, char *key) {
	if (get(map, key) != NULL) {
		return 1;
	}
	return 0;
}

int basicTest() {
	struct HashMap *map = constructHashMap();
	put(map, "George", "Washington");
	put(map, "John", "Adams");
	put(map, "Thomas", "Jefferson");
	put(map, "James", "Madison");
	put(map, "James", "Monroe");
	printf("%s\n", get(map, "George")->arr[0]); //should print "Washington".
	printf("%s\n", get(map, "James")->arr[0]); //should print "Madison".
	printf("%s\n", get(map, "James")->arr[1]); //should print "Monroe".
	printf("%d\n", map->size); //should print 5.
	struct Vector *tempOne = removeEntry(map, "Thomas");
	free(tempOne);
	printf("%d\n", map->size); //should print 4.
	struct Vector *tempTwo = removeEntry(map, "James");
	free(tempTwo);
	printf("%d\n", map->size); //should print 2.
	struct Vector *tempThree = removeEntry(map, "George");
	free(tempThree);
	struct Vector *tempFour = removeEntry(map, "John");
	free(tempFour);
	printf("%d\n", isEmpty(map)); //should print 1.
	return 1;
}

int scanTest() {
	struct HashMap *map = constructHashMap();
	char *iFilename = "input.txt";
	FILE *iFile = fopen(iFilename, "r");
	if (iFile == NULL) {
		printf("Error. Cannot open input file.");
		return 0;
	}
	char line[1024];
	while (fgets(line, 1024, iFile) != NULL) {
		int count = 0;
		while (line[count] != ':') {
			count += 1;
		}
		char *key = malloc(count + 1);
		memcpy(key, &line, count);
		key[count] = '\0';
		int length = strlen(line) - count;
		char *value = malloc(length);
		memcpy(value, &line[count + 1], length);
		put(map, key, value);
	}
	fclose(iFile);
	printf("%s", get(map, "George")->arr[0]);
	printf("%d", map->size);
	return 1;
}

int main() {
	return scanTest();
}
