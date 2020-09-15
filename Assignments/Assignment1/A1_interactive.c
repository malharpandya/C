/*
 *  CSC A48 - Winter 2019 - Assignment 1 starter
 *
 *  (c) 2020 Francisco Estrada
 *  - No part of this code may be reproduced without written authorization
 *
 * This file will test different components of your solution for assignment 1.
 * The actual solution you must implement will be in MDB-c.c.
 *
 * There is no code for you to implement here!
 *
 * Let us say that again:
 *
 * There is NO code for you to implement here.
 *
 * This file contains a little interface intended to help you test your
 * solution for part 1 manually, by entering movie review information and
 * carrying out operations from the terminal.
 *
 * Using this interface should be part of your process for making sure your
 * assignment solution works well!
 *
 * Once you have a complete solution, it should pass the entire set of
 * tests below.
 */

#include "MDB-c.c"  // <--- This will import your code so we can
                    //	use your solution to create a linked
                    //	list of movie reviews for testing!

/**
 * Reads a movie's name, title, and year from the terminal.
 * Required for inserting new reviews, search, updating, and deletion.
 *
 * INPUT: from terminal only
 *
 * OUTPUT:
 *  - title:
 *      an allocated char buffer (of length MAX_STR_LEN) in which the movie's title will be stored
 *  - studio:
 *      an allocated char buffer (of length MAX_STR_LEN) in which the movie's studio will be stored
 *  - year: an allocated integer buffer in which the movie's year will be stored
 */
void getTitleStudioYear(char title[MAX_STR_LEN], char studio[MAX_STR_LEN], int *year)
{
    printf("Please enter the movie's title:\n");
    fgets(title, MAX_STR_LEN, stdin);
    printf("Please enter the movie's studio:\n");
    fgets(studio, MAX_STR_LEN, stdin);
    printf("Please enter the movie's year:\n");
    scanf("%d", year);
    getchar();
}

/**
 * Reads a movie's Box-Office total and score from the terminal.
 * Required for inserting a new movie review, or for updating an existing review.
 *
 * INPUT: from terminal only
 *
 * OUTPUT:
 *  - BO_total:
 *      an allocated floating point buffer in which the movie's Box Office earnings will be stored
 *  - studio: an allocated integer buffer in which the movie's review score will be stored
 */
void getBOtotalScore(double *BO_total, int *score)
{
    printf("Please enter the Box Office total:\n");
    scanf("%lf", BO_total);
    getchar();
    printf("Please enter the review score:\n");
    scanf("%d", score);
    getchar();
}

int main()
{
    ReviewNode *MDB_head = NULL;
    ReviewNode *temp = NULL;
    int choice = 0;
    char title[MAX_STR_LEN];
    char studio[MAX_STR_LEN];
    char name[MAX_STR_LEN];
    int year;
    double BO_total;
    int score, count;

    while (true)
    {
        printf("Please choose one of the following options:\n");
        printf("1 - Insert a new movie review.\n");
        printf("2 - Search for a movie review.\n");
        printf("3 - Modify an existing movie review.\n");
        printf("4 - Delete a movie review.\n");
        printf("5 - Print out existing reviews.\n");
        printf("6 - Query reviews by studio.\n");
        printf("7 - Query reviews by score.\n");
        printf("8 - Sort reviews by movie title.\n");
        printf("9 - Insert cast member.\n");
        printf("10 - Count names in cast list.\n");
        printf("11 - Delete list of reviews and exit.\n");
        scanf("%d", &choice);
        getchar();

        // Read in review information from terminal where needed.
        if (choice >= 1 && choice <= 4)
        {
            getTitleStudioYear(title, studio, &year);
        }
        if (choice == 1 || choice == 3)
        {
            getBOtotalScore(&BO_total, &score);
        }
        if (choice == 1)
        {
            MDB_head = insertMovieReview(title, studio, year, BO_total, score, MDB_head);
        }
        else if (choice == 2)
        {
            temp = findMovieReview(title, studio, year, MDB_head);
            if (temp != NULL)
            {
                printf("Found the query movie:\n");
                printf("It had a box office total of %f\n", temp->review.BO_total);
                printf("And has a score of %d\n", temp->review.score);
            }
            else
            {
                printf("No such movie in the current list\n");
            }
        }
        else if (choice == 3)
        {
            updateMovieReview(title, studio, year, BO_total, score, MDB_head);
        }
        else if (choice == 4)
        {
            MDB_head = deleteMovieReview(title, studio, year, MDB_head);
        }
        else if (choice == 5)
        {
            printMovieReviews(MDB_head);
        }
        else if (choice == 6)
        {
            printf("Please enter the name of the studio you want to list movies for:\n");
            fgets(studio, MAX_STR_LEN, stdin);
            queryReviewsByStudio(studio, MDB_head);
        }
        else if (choice == 7)
        {
            printf("Enter the minimum score to be used to search for movies:\n");
            scanf("%d", &score);
            getchar();
            queryReviewsByScore(score, MDB_head);
        }
        else if (choice == 8)
        {
            printf("Sorting movies by title!\n");
            MDB_head = sortReviewsByTitle(MDB_head);
        }
        else if (choice == 9)
        {
            getTitleStudioYear(title, studio, &year);
            printf("Enter the name of the actor you want to add to this movie:\n");
            fgets(name, MAX_STR_LEN, stdin);
            insertCastMember(title, studio, year, MDB_head, name);
            printNames(findMovieReview(title, studio, year, MDB_head));
        }
        else if (choice == 10)
        {
            getTitleStudioYear(title, studio, &year);
            printf("Enter the name to count for appearances in the cast list:\n");
            fgets(name, MAX_STR_LEN, stdin);

            /* IMPORTANT - fgets will store the end of line '\n' character in
             * the name string, we have to remove it before matching or else
             * the function countNames() will try to match '\n' too! */
            name[strlen(name) - 1] = '\0';  // Why does this work?
            if(findMovieReview(title, studio, year, MDB_head) != NULL){
              count = countNames(&findMovieReview(title, studio, year, MDB_head)->review, name);
              printf("The name %s appears in the cast list:\n", name);
              printNames(findMovieReview(title, studio, year, MDB_head));
              printf("%d times.\n", count);
            }else{
              printf("%s\n","The movie does not exist!");
            }
        }else if (choice == 11)
        {
          MDB_head = deleteReviewList(MDB_head);
          printf("Done!\n");
          exit(0);
        }
    }
    return 0;
}
