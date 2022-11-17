int findClosestWin(int** board, int steps, int player) { // find closest win/loss for the PLAYER

    int count = 0;
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 7; j++)
            count = count + ((board[i][j] == 1 || board[i][j] == 2) ? 1 : 0);

    int minSteps = 100;
    int*** queue = (int***)(malloc(5000 * sizeof(int**))); // no more than 7^4 scenarios // steps cannot exceed 4
    if (queue != NULL)
        for (int i = 0; i < 5000; i++) {
            queue[i] = (int**)malloc(6 * sizeof(int*));
            if (queue[i] != NULL)
                for (int j = 0; j < 6; j++)
                    queue[i][j] = (int*)malloc(7 * sizeof(int));
        }

    int head = 0, tail = 0, size = 0;

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 7; j++)
            if (queue != NULL && queue[tail] != NULL && queue[tail][i] != NULL) // make sure all space was allocated
                queue[tail][i][j] = board[i][j];
    tail++;
    size++;

    // intialize current and temp
    int* current[6];
    int n0[7] = { 0,0,0,0,0,0,0 };
    current[0] = n0;
    int n1[7] = { 0,0,0,0,0,0,0 };
    current[1] = n1;
    int n2[7] = { 0,0,0,0,0,0,0 };
    current[2] = n2;
    int n3[7] = { 0,0,0,0,0,0,0 };
    current[3] = n3;
    int n4[7] = { 0,0,0,0,0,0,0 };
    current[4] = n4;
    int n5[7] = { 0,0,0,0,0,0,0 };
    current[5] = n5;

    int temp[6][7] = { {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0} };

    while (head < size) {

        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 7; j++)
                current[i][j] = queue[head][i][j];

        head++; // dequeue prev head
        size--;

        int indices[7] = { 6,6,6,6,6,6,6 }; // initialize all column indices to full

        int count1s = 0, count2s = 0;
        for (int i = 0; i < 7; i++)	// for each column
            for (int j = 0; j < 6; j++)	// record what row index we can insert at now
                if (current[j][i] == 0)
                    indices[i] = j;

                else if (current[j][i] == 1)
                    count1s++;
                else
                    count2s++;

        int numOfMoves = count2s + count1s - count;

        if (numOfMoves > steps)
            break;

        if (checkWin(current, 1)) {
            if (abs(minSteps) > numOfMoves)
                minSteps = (player == 1 ? 1 : -1) * numOfMoves;

            continue;
        }

        if (checkWin(current, 2))
        {
            if (abs(minSteps) > numOfMoves)
                minSteps = (player == 1 ? -1 : 1) * numOfMoves;

            continue;
        }


        for (int j = 0; j < 7; j++)	// add every possible neighbor (adding the number at each column)
        {

            if (indices[j] == 6) // cannot insert at this column
                continue;

            for (int k = 0; k < 6; k++)
                for (int l = 0; l < 7; l++)
                    temp[k][l] = current[k][l];

            temp[indices[j]][j] = count1s > count2s ? 2 : 1;	// choose player for this height
            for (int k = 0; k < 6; k++)
                for (int l = 0; l < 7; l++)
                    queue[tail][k][l] = temp[k][l];

            tail++; // enqueue neighbors
            size++;
        }

    }

    // deallocate space for queue
    for (int i = 0; i < 5000; i++) {
        if (queue[i] != NULL) {
            for (int j = 0; j < 6; j++) {
                free(queue[i][j]);
            }
            free(queue[i]);
        }
    }
    free(queue);

    return minSteps;
}