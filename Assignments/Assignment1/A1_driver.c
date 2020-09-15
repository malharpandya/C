/*
 *  CSC A48 - Winter 2020 - Assignment 1 test driver
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
 * There is NO code for you to implement here as part of the assignment.
 *
 * However:
 *
 * This file contains a sequence of tests that uses the different functions
 * your solution must provide.
 *
 * Have a look at how the tests work, and what is being tested. Think
 * about whether the tests are reasonable, and try to understand why
 * they would be needed to check for functionality.
 *
 * Think also about what additional tests *you should run* to fully
 * convince yourself your code works - As noted in the handout, passing
 * all the tests we provided does *not* guarantee your code is bug free,
 * you have to run your own tests and make sure it is so. You can add
 * your own tests to this file, but we won't look at them when
 * marking your solution.
 *
 * Tests are commented-out initially (because you haven't completed your
 * solution!). Uncomment the tests *as you work on your solution* to
 * test the parts you have completed.
 *
 * Once you have a complete solution, it should pass the entire set of
 * tests below.
 */

#include "MDB-c.c"  // <--- This will import your code so we can
                    //	use your solution to create a linked
                    //	list of movie reviews for testing!

int main()
{
    ReviewNode *MDB_head = NULL;
    ReviewNode *temp = NULL;
    CastList *casting = NULL;
    int length, count;

    ///  AUTOMATED TESTING SECTION
    ///  HOW TO USE THIS:
    ///
    ///   Once you implement parts of your solution, un-comment the relevant
    ///   tests below, and check your new code passes the corresponding tests.
    ///   Example: When you implement the insertMovieReview() function, you
    ///   should uncomment any tests that apply to insertMovieReview().
    ///
    ///   The ordering of the tests is intended to suggest the order in which
    ///   you should implement and test parts of your solution, but it's up to
    ///   you if you want to do this.
    ///
    ///   Passing all these tests will ensure your solution gets a solid mark
    ///   for the assignment, but the testing is not exhaustive, so passing
    ///   all tests here is *not* a guarantee that your code is bug free and
    ///   works under all conditions.
    ///
    ///   You should carry out your own testing and satisfy yourself that the
    ///   soution you implemented is correct.
    ///
    ///   Finally: Pay attention to how the tests are done, what is being tested,
    ///     what is expected, and how different parts of the test check for
    ///     specific things that must have happened if your solution is correct.
    ///     Doing this will help you develop the ability to write your own
    ///     tests, and will get you closer to being able to fully test code
    ///     by yourself when needed, in a way that lets you be confident your
    ///     programs work as intended.

    // Test #1: With an initially empty list, insert a new movie review.
    // Expects: The linked list should contain the new review after the test.
    MDB_head = insertMovieReview("Alien", "20th Century Fox", 1979, 203630630.0, 85, MDB_head);
    // Check whether the movie went into the linked list by accessing the
    // head node directly
    if (MDB_head == NULL)
    {
        printf("Failed Test #1 - insertMovieReview() returned NULL\n");
        return 1;
    }
    else
    {
        if (strcmp(MDB_head->review.movie_title, "Alien") != 0 ||
            strcmp(MDB_head->review.movie_studio, "20th Century Fox") != 0 ||
            MDB_head->review.year != 1979 || MDB_head->review.BO_total != (double)203630630.0 ||
            MDB_head->review.score != 85)
        {
            printf("Failed Test #1 - The movie information is incorrect\n");
            return 1;
        }
        // Check this node has a NULL pointer for the *next field (why is this
        // important?)
        if (MDB_head->next != NULL)
        {
            printf("Failed Test #1 - Head node's *next field is not NULL\n");
            return 1;
        }
    }
    printf("Passed Test #1\n");

     // Test #2: Insert another node into the list (which now has one movie)
     // Expects: The list should contain two reviews, in the right order
     temp = MDB_head;
     MDB_head = insertMovieReview("Raiders of the Lost Ark", "20th Century Fox", 1981, 389925971.00,
                                  85, MDB_head);

     // Check that the head node contains the new review.
     fprintf(stderr, "****%f\n", MDB_head->review.BO_total);
     if (strcmp("Raiders of the Lost Ark", MDB_head->review.movie_title) != 0)
     {
         printf("Failed Test #2: Movie data is incorrect!\n");
         return 1;
     }
     // Check linkage. The new head node's *next field should contain a pointer
     // to the old head of the list (which we conveniently saved)
     if (MDB_head->next != temp)
     {
         printf("Failed Test #2, the new head node is not linked to the old head node!\n");
         return 1;
     }
     else
     {
         // Check that the last node in the list has a NULL pointer in the *next field
         temp = MDB_head->next;
         if (temp->next != NULL)
         {
             printf("Failed Test #2, the last node has a non-NULL pointer in the *next field!\n");
             return 1;
         }
     }
     printf("Passed Test #2\n");

     // Test #3: Insert another node and check linkage of the list
     // Expects: The list should have 3 nodes, in the right order, with the right content.
     temp = MDB_head;
     MDB_head = insertMovieReview("Back to the Future", "Universal Studios", 1985, 381189762.00, 85,
                                  MDB_head);
     // Check that the head node contains the new review.
     if (strcmp("Back to the Future", MDB_head->review.movie_title) != 0)
     {
         printf("Failed Test #3: Movie data looks incorrect!\n");
         return 1;
     }
     if (MDB_head->next != temp)
     {
         printf("Failed Test #3, the new head node is not linked to the old head node!\n");
         return 1;
     }
     else
     {
         // Check the LAST node (there should be 3 now)
         temp = MDB_head->next;
         temp = temp->next;
         if (temp->next != NULL)
         {
             printf("Failed Test #3, the last node has a non-NULL pointer in the *next field!\n");
             return 1;
         }
         if (strcmp("Alien", temp->review.movie_title) != 0)
         {
             printf("Failed Test #3, the last node movie title is not correct!\n");
             return 1;
         }
     }
     printf("Passed Test #3\n");

     // Test #4: Test the countReviews() function
     // Expects: The correct list length must be returned
     length = countReviews(MDB_head);
     if (length != 3)
     {
         printf(
             "Failed Test #4: There should be 3 reviews at this point, countReviews() returned %d\n",
             length);
         return 1;
     }
     printf("Passed Test #4\n");

     // Test #5: Insert a duplicate review
     // Expects: No duplicate should be inserted into the list
     temp = MDB_head;
     MDB_head = insertMovieReview("Raiders of the Lost Ark", "20th Century Fox", 1981, 389925971.00,
                                  85, MDB_head);
     if (temp != MDB_head || countReviews(MDB_head) != length)
    {
         printf("Failed Test #5: The insert function updated the list with a duplicate\n");
         return 1;
     }
     printf("Passed Test #5\n");

     // Test #6: Insert a near-duplicate
     // Expects: Near duplicates are allowed, so a new node must be added, length should be 4
     temp = MDB_head;
     MDB_head = insertMovieReview("Alien", "20th Century Fox", 1978, 203630630.0, 85, MDB_head);
     length = countReviews(MDB_head);
     if (length != 4 || MDB_head->next != temp || MDB_head->review.year != 1978)
     {
         printf(
             "Failed Test 6: The list does not have the right length, or it's not properly linked, "
             "or has the wrong content\n");
         return 1;
     }
     printf("Passed test #6\n");

     // Test #7: Test the search function for an existing movie
     // Expects: The search function must return a pointer to the movie review matching the query
     temp = findMovieReview("Alien", "20th Century Fox", 1979, MDB_head);
     if (temp == NULL)
     {
         printf("Failed Test #7: the find function did not find the movie.\n");
         return 1;
     }
     else
     {
         if (strcmp("Alien", temp->review.movie_title) != 0 ||
             strcmp("20th Century Fox", temp->review.movie_studio) != 0 || temp->review.year != 1979)
         {
             printf("Failed Test #7: the find function did not check all fields match\n");
             return 1;
         }
     }
     printf("Passed Test #7\n");

     // Test #8: Test the search function for a non-existing movie
     // Expects: The search function must return NULL
     temp = findMovieReview("Alienized", "21st Century Fox", 2979, MDB_head);
     if (temp != NULL)
     {
         printf(
             "Failed Test #8: The search function returned a non-NULL node for a non-existing "
             "movie!\n");
         return 1;
     }
     printf("Passed Test #8\n");

     // Test #9: Test the update review function
     // Expected: The requested review must have its information updated
     updateMovieReview("Back to the Future", "Universal Studios", 1985, 5000000000, 99, MDB_head);
     temp = findMovieReview("Back to the Future", "Universal Studios", 1985, MDB_head);
     if (temp == NULL)
     {
         printf("Failed Test #9: Can't find updated review\n");
         return 1;
     }
     else
     {
         if (temp->review.BO_total != (double)5000000000 || temp->review.score != 99)
         {
             printf("Failed Test #9: Review information was not updated\n");
             return 1;
         }
     }
     printf("Passed Test #9\n");

     // Test #10: Test deletion of a review within the linked list (not head, not tail)
     // Expected: The review should be deleted, list length should be 3 after deletion
     temp = MDB_head;
     MDB_head = deleteMovieReview("Raiders of the Lost Ark", "20th Century Fox", 1981, MDB_head);
     length = countReviews(MDB_head);
     if (temp != MDB_head)
     {
         printf("Failed Test #10: The list head changed\n");
         return 1;
     }
     if (length != 3)
     {
         printf("Failed Test #10: The list has the wrong length\n");
         return 1;
     }
     temp = findMovieReview("Raiders of the Lost Ark", "20th Century Fox", 1981, MDB_head);
     if (temp != NULL)
     {
         printf(
             "Failed Test #10: The requested movie was found in the list - the wrong thing got "
             "deleted!\n");
         return 1;
     }
     printf("Passed Test #10\n");

     // Test #11: Test deletion of a review at the head of the list
     // Expected: The review should be deleted, list length should be 2.
     temp = MDB_head;
     MDB_head = deleteMovieReview("Alien", "20th Century Fox", 1978, MDB_head);
     length = countReviews(MDB_head);
     if (temp == MDB_head)
     {
         printf("Failed Test #11: The delete function did not remove the head node\n");
         return 1;
     }
     if (length != 2)
     {
         printf("Failed Test #11: The list length is wrong\n");
         return 1;
     }
     if (strcmp("Back to the Future", MDB_head->review.movie_title) != 0)
     {
         printf("Faied Test #11: The wrong node is at the head of the list\n");
         return 1;
     }
     printf("Passed Test #11\n");

     // Test #12: Query functions - queryReviewsByScore()
     // Expected: The function should print any reviews with a score equal to or greater than
     //  the query value
     printf("Passed Test #12?\n");
     printf(" YOU have to check this prints (updated) Back to the Future with a score of 99:\n");
     queryReviewsByScore(95, MDB_head);

     // Test #13: Insert a cast member into a movie that initially has none
     // Expected: We should find the cast member's name at the first entry of the linked
     // list for the cast.
     insertCastMember("Back to the Future", "Universal Studios", 1985, MDB_head, "Michael J. Fox");
     temp = findMovieReview("Back to the Future", "Universal Studios", 1985, MDB_head);
     if (temp == NULL)
     {
         printf("Failed test #13, the updated movie could not be found in the database!\n");
         return 1;
     }
     if (temp->review.cast == NULL)
     {
         printf("Failed test #13, the movie still has an empty cast after inserting a name!\n");
         return 1;
     }
     casting = temp->review.cast;
     if (strcmp(&casting->name[0], "Michael J. Fox"))
     {
         printf("Failed test #13, the name in the cast list is not correct!\n");
         return 1;
     }
     printf("Passed Test #13\n");

     // Test #14: Insert more cast members and check the function that counts the number of
     // times a certain name appears in the cast list.
     insertCastMember("Back to the Future", "Universal Studios", 1985, MDB_head,
                      "Christopher Lloyd Fox");
     insertCastMember("Back to the Future", "Universal Studios", 1985, MDB_head, "Lea fox Thompson");
     insertCastMember("Back to the Future", "Universal Studios", 1985, MDB_head,
                      "Crispin GloverFox");
     count = countNames(&temp->review, "Fox");
     printf("The name 'Fox' appears in the cast list %d times\n", count);
     if (count != 3)
     {
         printf("Failed test #14, the count should be 3\n");
         return 1;
     }
     printf("Passed Test #14\n");

     // Test #15: Deleting a linked list
     // Expected: The list should be deleted and the MDB_head pointer should be NULL
     MDB_head = deleteReviewList(MDB_head);
     if (MDB_head != NULL)
     {
         printf("Failed Test #15: The list head pointer is not NULL\n");
         return 1;
     }
     else if (countReviews(MDB_head) != 0)
     {
         printf("Failed Test #15: countReviews() returns %d reviews still in the list\n",
                countReviews(MDB_head));
         return 1;
     }
     printf("Passed Test #15\n");

    printf("Congratulations! your solution passed all the tests you un-commented!\n");
    printf(
        "Remember to run your own tests as well to make sure your code works under all "
        "conditions\n");

    return 0;  // All good!
}
