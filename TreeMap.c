#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int INITIAL_CAPACITY = 10;

struct Vector {
	char **arr;
	int size;
	int capacity;
};

struct MapEntry {
	char *key;
	struct Vector *values;
	struct MapEntry *left;
	struct MapEntry *right;
};

struct TreeMap {
	struct MapEntry *root;
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
	entry->left = NULL;
	entry->right = NULL;
	return entry;
}

struct TreeMap *constructTreeMap() {
	struct TreeMap *map = malloc(sizeof(struct TreeMap));
	map->root = NULL;
	map->size = 0;
	return map;
}

void deconstructVector(struct Vector *vec) {
	int i;
	for (i = 0; i < vec->size; i += 1) {
		free(vec->arr[i]);
	}
	free(vec->arr);
	free(vec);
}

void deconstructMapEntry(struct MapEntry *entry) {
	deconstructVector(entry->values);
	free(entry->key);
	free(entry);
}

void deconstructTree(struct MapEntry *entry) {
	if (entry != NULL) {
		deconstructTree(entry->left);
		deconstructTree(entry->right);
		deconstructMapEntry(entry);
	}
}

void deconstructTreeMap(struct TreeMap *map) {
	deconstructTree(map->root);
	free(map);
}

void putHelp(struct TreeMap *map, struct MapEntry *entry,
		char *key, char *value) {
	int cmp = strcmp(key, entry->key);
	if (cmp == 0) {
		push_back(entry->values, value);
		map->size += 1;
	} else if (cmp < 0) {
		if (entry->left == NULL) {
			entry->left = constructMapEntry(key, value);
			map->size += 1;
		} else {
			putHelp(map, entry->left, key, value);
		}
	} else {
		if (entry->right == NULL) {
			entry->right = constructMapEntry(key, value);
			map->size += 1;
		} else {
			putHelp(map, entry->right, key, value);
		}
	}
}

void put(struct TreeMap *map, char *key, char *value) {
	if (map == NULL || key == NULL || value == NULL) {
		printf("Error. Null argument.");
		exit(1);
	}
	if (map->root == NULL) {
		map->root = constructMapEntry(key, value);
		map->size += 1;
	} else {
		putHelp(map, map->root, key, value);
	}
}

struct MapEntry *replace(struct TreeMap *map, struct MapEntry *entry);

struct MapEntry *successor(struct TreeMap *map, struct MapEntry *entry) {
	if (entry->left->left == NULL) {
		struct MapEntry *temp = entry->left;
		entry->left = replace(map, entry->left);
		return temp;
	}
	return successor(map, entry->left);
}

struct MapEntry *replace(struct TreeMap *map, struct MapEntry *entry) {
	if (entry->left == NULL) {
		struct MapEntry *temp = entry->right;
		free(entry);
		return temp;
	}
	if (entry->right == NULL) {
		struct MapEntry *temp = entry->left;
		free(entry);
		return temp;
	}
	if (entry->right->left == NULL) {
		struct MapEntry *temp = entry->right;
		temp->left = entry->left;
		free(entry);
		return temp;
	}
	struct MapEntry *temp = successor(map, entry->right);
	temp->left = entry->left;
	temp->right = entry->right;
	free(entry);
	return temp;
}

struct Vector *removeHelp(struct TreeMap *map, struct MapEntry *entry, char *key) {
	if (strcmp(key, entry->key) < 0) {
		if (entry->left == NULL) {
			return NULL;
		}
		if (strcmp(key, entry->left->key) == 0) {
			struct Vector *result = entry->left->values;
			entry->left = replace(map, entry->left);
			map->size -= result->size;
			return result;
		} else {
			return removeHelp(map, entry->left, key);
		}
	} else {
		if (entry->right == NULL) {
			return NULL;
		}
		if (strcmp(key, entry->right->key) == 0) {
			struct Vector *result = entry->right->values;
			entry->right = replace(map, entry->right);
			map->size -= result->size;
			return result;
		} else {
			return removeHelp(map, entry->right, key);
		}
	}
}

struct Vector *removeEntry(struct TreeMap *map, char *key) {
	if (map == NULL || key == NULL) {
		printf("Error. Null argument.");
		exit(1);
	}
	if (map->root == NULL) {
		return NULL;
	}
	struct Vector *result;
	if (strcmp(key, map->root->key) == 0) {
		result = map->root->values;
		map->root = replace(map, map->root);
		map->size -= result->size;
	} else {
		result = removeHelp(map, map->root, key);
	}
	return result;
}

struct Vector *getHelp(struct TreeMap *map, struct MapEntry *entry, char *key) {
	if (entry == NULL) {
		return NULL;
	}
	int cmp = strcmp(key, entry->key);
	if (cmp == 0) {
		return entry->values;
	} else if (cmp < 0) {
		return getHelp(map, entry->left, key);
	} else {
		return getHelp(map, entry->right, key);
	}
}

struct Vector *get(struct TreeMap *map, char *key) {
	if (map == NULL || key == NULL) {
		printf("Error. Null argument.");
		exit(1);
	}
	return getHelp(map, map->root, key);
}

int isEmpty(struct TreeMap *map) {
	if (map->size == 0) {
		return 1;
	}
	return 0;
}

int containsKey(struct TreeMap *map, char *key) {
	if (get(map, key) != NULL) {
		return 1;
	}
	return 0;
}

int basicTest() {
	struct TreeMap *map = constructTreeMap();
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
	deconstructTreeMap(map);
	return 1;
}

int scanTest() {
	struct TreeMap *map = constructTreeMap();
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
	deconstructTreeMap(map);
	return 1;
}

int main() {
	return scanTest();
}
