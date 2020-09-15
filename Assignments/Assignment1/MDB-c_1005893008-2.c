/**
 *  CSC A48 - Winter 2020 - Assignment 1 starter
 *
 *  (c) 2020 Francisco Estrada & Joe Armitage
 *  - No part of this code may be reproduced without written authorization
 *
 * This is the file where you will be doing most of your work. The
 * functionality you must provide for part 1 of the assignment is described
 * in the handout, and given in detail in the comments at the head of each
 * function below.
 *
 * Plan your work carefully, review the notes for Unit 3, and work carefully
 * to complete the functions in this file. At any point you can bring
 * questions to your TAs or instructors during office hours. But please
 * remember:
 *
 * - You should not post any assignment code on Piazza
 * - You should not share any part of your solution in any form
 * - You should definitely *help* other understand any ideas and
 *   concepts regarding linked lists that you have already mastered,
 *   but being careful not to give away parts of the solution, or
 *   descriptions of how to implement functions below.
 * - If you are not sure whether you can or can not discuss some
 *   particular aspect of the work to be done, remember it's always
 *   safe to talk with your TAs.
 * - Obtaining external 'help' including being given code by an
 *   external party, or being tutored on what to write to solve
 *   the assignment constitutes an academic offence.
 *
 * All tasks to be completed by you are clearly labeled with a
 * TODO:
 * comment block, which also gives you details about what you have to implement.
 * Look carefully and make sure you don't miss a thing!
 *
 * NOTE: This file contains no main() function! you can not compile
 * it on its own to create an executable. It's meant to be used
 * together with A1_driver.c - be sure to read that file carefully
 * to understand how to use the tests there - Any additional tests
 * you want to run on the code below should be added to A1_driver.c
 *
 * Before you even get starter implementing, please complete the
 * student identification section below, and check that you are aware
 * of the policy on academic honesty and plagiarism.
 */

/**
 * TODO: STUDENT IDENTIFICATION
 *
 * Student Name (Last name, First name): Pandya, Malhar
 * Student Number: 1005893008
 * UTORid: pandyam8
 * Your instructor's name is: Francisco Estrada
 */

/**
 * TODO:
 * Academic Integrity Statement:
 *
 * I hereby certify that the work contained in this file is my own, and
 * that I have not received any parts of my solution from other sources
 * including my fellow students, external tutoring services, the internet,
 * or algorithm implementations found online.
 *
 * Sign here with your name: Malhar Pandya
 *
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 1024

typedef struct castList_struct
{
    char name[MAX_STR_LEN];
    struct castList_struct *next;
} CastList;

typedef struct movieReview_struct
{
    char movie_title[MAX_STR_LEN];
    char movie_studio[MAX_STR_LEN];
    int year;
    double BO_total;
    int score;
    CastList *cast;
} MovieReview;

typedef struct reviewNode_struct
{
    MovieReview review;
    struct reviewNode_struct *next;
} ReviewNode;

ReviewNode *newMovieReviewNode(char *title, char *studio, int year, double BO_total, int score)
{
    // Check if the user input is valid. Proceed if valid, else return NULL.
    if(year < 1920 || year > 2999 || BO_total < 0 || score < 0 || score > 100 || strlen(title) > MAX_STR_LEN || strlen(studio) > MAX_STR_LEN) return NULL;
    // Declare Review Node and assign input.
    ReviewNode *newMovieReview = NULL;
    newMovieReview = (ReviewNode *)calloc(1, sizeof(ReviewNode));
    // Check if memory was allocated.
    if(newMovieReview != NULL)
    {
        strcpy(newMovieReview->review.movie_title,title);
        strcpy(newMovieReview->review.movie_studio,studio);
        newMovieReview->review.year = year;
        newMovieReview->review.BO_total = BO_total;
        newMovieReview->review.score = score;
        newMovieReview->review.cast = NULL;
        newMovieReview->next = NULL;
    }
    // Return pointer to ReviewNode.
    return newMovieReview;
}

ReviewNode *findMovieReview(char *title, char *studio, int year, ReviewNode *head)
{
    // Declare a pointer to head.
    ReviewNode *p = NULL;
    p = head;
    // Loop over linked list.
    while(p != NULL)
    {
        // Check for matching data and return pointer to matching review, else proceed to next review.
        if(strcmp(p->review.movie_title, title) == 0 && strcmp(p->review.movie_studio, studio) == 0 && p->review.year == year) return p;
        p = p->next;
    }
    // Return NULL on exhaustion.
    return NULL;
}

ReviewNode *insertMovieReview(char *title, char *studio, int year, double BO_total, int score,
                              ReviewNode *head)
{
    // Check existing linked list for matching review. Proceed if not found, else give error message and return head.
    if(findMovieReview(title, studio, year, head) != NULL)
    {
        printf("Sorry, that movie already exists\n");
        return head;
    }
    // Declare new_node and assign input using newMovieReviewNode().
    ReviewNode *new_node = NULL;
    new_node = newMovieReviewNode(title, studio, year, BO_total, score);
    // Check if user input is valid. Return head if invalid.
    if(new_node == NULL) return head;
    // Link new_node to head of linked list and return it.
    new_node->next = head;
    return new_node;
}

int countReviews(ReviewNode *head)
{
    // Declare and initialise pointer to head and review counter to 0.
    int counter = 0;
    ReviewNode *p = NULL;
    p = head;
    // Loop over linked list and track number of iterations.
    while(p != NULL)
    {
        counter++;
        p = p->next;
    }
    // return number of iterations on exhaustion.
    return counter;
}

void updateMovieReview(char *title, char *studio, int year, double BO_total, int score,
                       ReviewNode *head)
{
    // Check if input is valid.
    if(BO_total >= 0 && score >= 0 && score <= 100)
    {
        // Declare and initialise pointer to review to be updated via findMovieReview().
        ReviewNode *p = NULL;
        p = findMovieReview(title, studio, year, head);
        // Check if review exists in linked list, give error message if it doesn't.
        if(p == NULL)
        {
            printf("Sorry, no such movie exists at this point\n");
        }
        // Update review with user input.
        else
        {
            p->review.BO_total = BO_total;
            p->review.score = score;
        }
    }
}

ReviewNode *deleteMovieReview(char *title, char *studio, int year, ReviewNode *head)
{
    // Declare 2 pointers tr and pre.
    ReviewNode *tr = NULL;
    ReviewNode *pre = NULL;
    // Declare and initialise pointer "one_review" to review to be deleted via findMovieReview.
    ReviewNode *one_review = findMovieReview(title, studio, year, head);
    // Return NULL if linked list is empty.
    if (head == NULL) return NULL;
    // Initialise pre to head, tr to head->next respectively.
    pre = head;
    tr = head->next;
    // Check if review to be deleted is at head. If true, free head and return tr.
    if(one_review == head)
    {
        free(pre);
        return tr;
    }
    // Loop over list using tr.
    while(tr != NULL)
    {
        // Check if tr is one_review. If true, assign tr->next to pre->next, free tr and break loop. Else proceed both pointers to their respective next values.
        if(one_review == tr)
        {
            pre->next = tr->next;
            free(tr);
            break;
        }
        tr = tr->next;
        pre = pre->next;
    }
    // Return head if review did not exist in the linked list or is deleted from linked list.
    return head;
}

double printMovieReviews(ReviewNode *head)
{
    // Initialise box office counter to 0. Declare and initialise pointer to head.
    double box_office_total = 0;
    ReviewNode *p = NULL;
    p = head;
    // Loop over linked list and print each review and add respective BO_total to box office counter.
    while(p != NULL)
    {
        box_office_total += p->review.BO_total;
        printf("%s\n", p->review.movie_title);
        printf("%s\n", p->review.movie_studio);
        printf("%d\n", p->review.year);
        printf("%lf\n", p->review.BO_total);
        printf("%d\n", p->review.score);
        printf("********************\n");
        p = p->next;
    }
    // Return box office counter.
    return box_office_total;
}

double queryReviewsByStudio(char *studio, ReviewNode *head)
{
    // Initialise box office counter to 0. Declare and initialise pointer to head.
    double box_office_studio = 0;
    ReviewNode *p = NULL;
    p = head;
    // Loop over linked list.
    while(p != NULL)
    {
        // check if studio in review matches user input. If true, print review and add BO_total to box office counter, else proceed to next review.
        if(strcmp(p->review.movie_studio, studio)==0)
        {
            box_office_studio += p->review.BO_total;
            printf("%s\n", p->review.movie_title);
            printf("%s\n", p->review.movie_studio);
            printf("%d\n", p->review.year);
            printf("%lf\n", p->review.BO_total);
            printf("%d\n", p->review.score);
            printf("********************\n");
        }
        p = p->next;
    }
    // Return box office counter.
    return box_office_studio;
}

double queryReviewsByScore(int min_score, ReviewNode *head)
{
    // Initialise box office counter to 0. Declare and initialise pointer to head.
    double box_office_score = 0;
    ReviewNode *p = NULL;
    p = head;
    // Loop over linked list.
    while(p != NULL)
    {
        // check if score in review is greater than or equal to user input. If true, print review and add BO_total to box office counter, else proceed to next review.
        if(p->review.score >= min_score)
        {
            box_office_score += p->review.BO_total;
            printf("%s\n", p->review.movie_title);
            printf("%s\n", p->review.movie_studio);
            printf("%d\n", p->review.year);
            printf("%lf\n", p->review.BO_total);
            printf("%d\n", p->review.score);
            printf("********************\n");
        }
        p = p->next;
    }
    // Return box office counter.
    return box_office_score;
}

ReviewNode *deleteReviewList(ReviewNode *head)
{
    // Declare 2 pointers p and q.
    ReviewNode *p = NULL;
    ReviewNode *q = NULL;
    // Initialise p to head.
    p = head;
    // Loop over linked list.
    while(p != NULL)
    {
        // Initialise q to p->next, free p and assign q to p.
        q = p->next;
        free(p);
        p = q;
    }
    // Return NULL once linked list is deleted.
    return NULL;
}

ReviewNode *sortReviewsByTitle(ReviewNode *head)
{
    // NOTE: since MovieReview is a fairly small data type, storing it in a temporary location is not an issue, and so it would be better to use the easier method of swapping the data. As swapping data requires 1 swap, and swapping pointers will usually require 2 swaps.
    // Declare and initialise 2 pointers to head.
    ReviewNode *p = NULL;
    ReviewNode *q = NULL;
    p = head;
    q = head;
    // Declare variable of type MovieReview.
    MovieReview temp;
    // Loop over length of linked linked list. (very poor bubble sort algorithm O(n * n)).
    while(p != NULL)
    {
        // Loop over each item in the linked list.
        while (q->next != NULL)
        {
            // Compare adjacent reviews and swap if required.
            int title = strcmp(q->review.movie_title, q->next->review.movie_title);
            int studio = strcmp(q->review.movie_studio, q->next->review.movie_studio);
            // More recent movie remakes come up earlier in the linked list.
            int year = q->review.year - q->next->review.year;
            if(title > 0 || (title == 0 && studio > 0) || (title == 0 && studio == 0 && year < 0))
            {
                temp = q->review;
                q->review = q->next->review;
                q->next->review = temp;
            }
            q = q->next;
        }
        q = head;
        p = p->next;
    }
    return head;
}

void insertCastMember(char *title, char *studio, int year, ReviewNode *head, char *name)
{
    // Declare a pointer to a review.
    ReviewNode *p = NULL;
    // Initialise the pointer to the review whose Castlist we have to update.
    p = findMovieReview(title, studio, year, head);
    // Check if review is in linked list.
    if(p != NULL)
    {
        // Declare a Castlist and initialise name with user input.
        CastList *new_cast = NULL;
        new_cast = (CastList *)calloc(1, sizeof(CastList));
        // Check if memory was allocated.
        if(new_cast != NULL)
        {
            strcpy(&new_cast->name[0], name);
            // Check if castlist of review is non empty.
            if(p->review.cast != NULL)
            {
                new_cast->next = p->review.cast;
            }
            p->review.cast = new_cast;
        }
    }
}

int countNames(MovieReview *movie, char *name)
{
    // Initialise counter to 0. Declare a pointer to a Castlist.
    int name_count = 0;
    CastList *p = NULL;
    // Check if review exists in linked list before dereferencing pointer to the Castlist of that review.
    if(movie != NULL) p = movie->cast;
    // Looping over the Castlist.
    while(p != NULL)
    {
        // Adding to counter each time user input is substring of castmember.
        if(strstr(p->name, name) != NULL)
        {
            name_count++;
        }
        p = p->next;
    }
    // Return counter.
    return name_count;
}

 void printNames(ReviewNode *head)
 {
     if (NULL == head || NULL == head->review.cast) return;
     printf("The cast for this movie are:\n");
     for (CastList *p = head->review.cast; NULL != p; p = p->next) printf("%s\n", p->name);
 }
