#include <pthread.h>

pthread_mutex_t mutex1 = PTHRED_MUTEX_INITIALIZER;

void *downtime()
{
    Node *balance_root;
    Node *root;

    // Downtime 1
    sleep(2);
    pthread_mutex_lock(&mutex1);
    balance_root = balanceTree(root);
    subtreeFree(balance_root);
    balance_root = NULL;
    pthread_mutex_unlock(&mutex1);

    // Downtime 2
    sleep(2);
    pthread_mutex_lock(&mutex1);
    balance_root = balanceTree(root);
    subtreeFree(balance_root);
    balance_root = NULL;
    pthread_mutex_unlock(&mutex1);

        // Downtime 3
    sleep(2);
    pthread_mutex_lock(&mutex1);
    balance_root = balanceTree(root);
    subtreeFree(balance_root);
    balance_root = NULL;
    pthread_mutex_unlock(&mutex1); 
    return NULL;
}

void *ServeClient(char *client)
{
    char line(100);
    FILE *files;
    files = fopen(client, "r");
    int value;
    int sum;

    if (files == NULL)
    {
        printf("File did not open. %s", client);
    }

    while (fscanf(fp, "%s, %d", line, &value) != EOF)
    {
        if (strcmp(line, "addNode") == 0)
        {
            pthread_mutex_lock(&mutex1);
            root = addNode(root, value);
            printf("[%s]insertNode %d\n", client, value);
            pthread_mutex_unlock(&mutex1);
        }
        else if (strcmp(line, "removeNode") == 0)
        {
            pthread_mutex_lock(&mutex1);
            root = removeNode(root, value);
            printf("[%s]deleteNode %d\n", client, value);
            pthread_mutex_unlock(&mutex1);
        }
        else if (strcmp(line, "countNodes") == 0)
        {
            pthread_mutex_lock(&mutex1);
            sum = countNodes(root);
            printf("[%s]%s %d\n", client, line, sum);
            pthread_mutex_unlock(&mutex1);
        }
        else if (strcmp(line, "avgSubtree") == 0)
        {
            pthread_mutex_lock(&mutex1);
            average = avgSubTree(root);
            printf("[%s]%s %f\n", client, line, average);
            pthread_mutex_unlock(&mutex1);
        }

        fclose(files);
        return NULL;
    }
}
