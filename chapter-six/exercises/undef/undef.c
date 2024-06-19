/* undef:  remove a name and definition from the table */
void undef(char *s)
{
    struct nlist *np, *prev;

    prev = NULL;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
	if (strcmp(s, np->name) == 0)
	    break;
	prev = np;
    }
    if (np != NULL) {
	if (prev == NULL)
	    hashtab[hash(s)] = np->next;
	else
	    prev->next = np->next;
	free((void *) np->name);
	free((void *) np->defn);
	free((void *) np);
    }
}

