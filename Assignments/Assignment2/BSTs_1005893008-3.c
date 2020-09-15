/*
  CSC A48 - Assignment 2 - BSTs, Traversals, a tiny Sequencer

  For this assignment you will be implementing a fully working
  BST. The goal is for you to gain practice with one of the most
  common and more useful data structures you can find.

  The data we will store in the BST corresponds to musical notes
  from a little song, and we have provided (in a separate .c
  file) a very small implementation of a program to making
  sounds from each of these musical notes.

  ** YOU DO NOT NEED TO look at that code
  ** Everything in 'NoteSynth.c' is provided
  ** just so you can listen to the data in your
  ** BST - but you do not need to look at it for
  ** this assignment, and you're not expected
  ** to learn or understand that code.

  You can, however, learn from it if you're curious about how
  sound can be synthesized. Don't spend time on that unless you
  have completed everything else.

  Read carefully the comments and descriptions in this starter
  code, as they constitute the specification of what you need
  to do to complete the assignment.

  - Like A1, we will provide a test driver for you to test your
    code. Also like A1, that test driver contains a subset of the
    tests we will be running. You are responsible for running
    additional tests to ensure your BST works properly!

 Starter code (c) 2019 - F. Estrada, M. Ahmadzadeh
*/

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"NoteSynth.c"

typedef struct BST_Node_Struct
{
    // This compound type stores all data for one node of the
    // BST. Since the BST is used to store musical notes,
    // the data contained here represents one note from a
    // musical score:
    // freq: A double-precision floating point value,
    //       corresponding to the frequency (pitch) of the note
    // bar: Musical scores are divided into 'bars' (which you can
    //      see are actually separated by a vertical bar!). This
    //      value indicates which bar the note happens in. The
    //      first bar in the musical score is 0
    // index: Position of the note within the bar, from 0 (at the
    //        beginning of the bar) to 1 (at the end of the bar)
    // key: A unique identifier (remember we discussed BST nodes
    //      should have unique keys to identify each node). We
    //      want our nodes to store notes in the order in which
    //      they occur in the song. So, the key identifier is
    //      created as: key = (10.0*bar)+index
    //      NOTE: This means only one note can have a specific
    //            bar,index value. If two notes should happen
    //            at the same time in the song, we make the
    //            index of one of them a tiny bit bigger or
    //            a tiny bit smaller than the other one so
    //            their keys are very close, but not identical.

    double key;
    double freq;
    int bar;
    double index;
    struct BST_Node_Struct *left;
    struct BST_Node_Struct *right;
} BST_Node;

BST_Node *newBST_Node(double freq, int bar, double index)
{
    // Dynamically allocate a new node.
    BST_Node *new_note = NULL;
    new_note = (BST_Node *)calloc(1, sizeof(BST_Node));
    // Check validity of parameters.
    if (freq <= 0 || bar < 0 || index < 0 || index > 1 || new_note == NULL) return NULL;
    // Initialise the node with given parameters.
    new_note->freq = freq;
    new_note->bar = bar;
    new_note->index = index;
    new_note->key = (10.0 * bar) + index;
    // Initialise children nodes to NULL.
    new_note->left = NULL;
    new_note->right = NULL;
    // Return the node.
    return new_note;
    /*
     * This function creates and initializes a new BST_Node
     * for a note with the given position (bar:index) and
     * the specified frequency. The key value for the node
     * is computed here as
     *
     *         (10.0*bar)+index
     */
}

BST_Node *BST_insert(BST_Node *root, BST_Node *new_node)
{
    // Check if tree exists, if not return node.
    if (root == NULL) return new_node;
    // Traverse through tree by comparing keys using recursion.
    if (new_node->key > root->key) root->right = BST_insert(root->right, new_node);
    else if (new_node->key < root->key)root->left = BST_insert(root->left, new_node);
    // Check for duplicates.
    else printf("Duplicate node requested (bar:index)=%d,%lf, it was ignored\n", root->bar, root->index);
    return root;
    /*
     * This function inserts a new node into the BST. The
     * node must already have been initialized with valid
     * note data, and must have its unique key.
     *
     * The insert function must check that no other node
     * exists in the BST with the same key. If a node with
     * the same key exists, it must print out a message
     * using the following format string
     *
     * printf("Duplicate node requested (bar:index)=%d,%lf, it was ignored\n",....);
     * (of course you need to provide the relevant variables to print)
     *
     * And it must return without inserting anyting in the
     * BST.
     */
}

BST_Node *BST_search(BST_Node *root, int bar, double index)
{
    // Check if tree exists, if not return NULL.
    if (root == NULL) return NULL;
    // Declare the key to be compared.
    double key_tmp = (10.0 * bar) + index;
    // Compare the keys, return if equal.
    if (root->key == key_tmp) return root;
    // Proceed to the correct subtree and repeat search.
    if (key_tmp > root->key) return BST_search(root->right, bar, index);
    return BST_search(root->left, bar, index);
    /*
     * This function searches the BST for a note at the
     * speficied position. If found, it must return a
     * pointer to the node that contains it.
     * Search has to happen according to the BST search
     * process - so you need to figure out what value to
     * use during the search process to decide which branch
     * of the tree to search next.
     */
}

BST_Node *find_successor(BST_Node *right_child_node)
{
    // Check if input is not NULL.
    if (right_child_node == NULL) return NULL;
    // Traverse to the left child node untill it becomes NULL.
    BST_Node *traversal = right_child_node;
    while (traversal->left != NULL) traversal = traversal->left;
    return traversal;
    /*
     * This function finds the successor of a node by
     * searching the right subtree for the node that
     * is most to the left (that will be the node
     * with the smallest key in that subtree)
     */
}

BST_Node *BST_delete(BST_Node *root, int bar, double index)
{
    // Declare the key to be found.
    double key_tmp = (10.0 * bar) + index;
    BST_Node *tmp;
    // Check if tree exists, if not return NULL.
    if (root == NULL) return NULL;
    // compare keys.
    if (key_tmp == root->key){
        // Case 1: node to be deleted has atmost 1 child node.
        if (root->right == NULL){
            tmp = root->left;
            free (root);
            return tmp;
        }
        else if (root->left == NULL){
            tmp = root->right;
            free (root);
            return tmp;
        }
        // Case 2: node to be deleted has 2 children nodes.
        else{
            // Find successor.
            tmp = find_successor(root->right);
            // Copy data to node to be deleted.
            root->bar = tmp->bar;
            root->freq = tmp->freq;
            root->index = tmp->index;
            root->key = tmp->key;
            // Delete successor.
            root->right = BST_delete(root->right, tmp->bar, tmp->index);
        }
    }
    // Proceed to the correct subtree and apply recursion.
    else if (key_tmp >root->key) root->right = BST_delete(root->right, bar, index);
    else root->left = BST_delete(root->left, bar, index);
    // Return root if node does not exist in tree.
    return root;
    /*
     * Deletes from the BST a note at the specified position.
     * You must implement the three cases of BST deletion
     * we discussed in class. Make sure the function can
     * remove a note at any position without breaking the
     * tree!
     */
}

void BST_makePlayList(BST_Node *root)
{
    // Check if tree is empty.
    if (root == NULL) return;
    // Apply in-order traversal.
    BST_makePlayList(root->left);
    // Apply operation.
    playlist_head = playlist_insert(playlist_head, root->freq, root->bar, root->index);
    BST_makePlayList(root->right);
    /*
     * This function does an in-order traversal of the BST to
     * generate an ordered list of notes to be played. Each
     * note is added to a linked-list (already implemented,
     * you only need to call the insert function) and the
     * play list is then playable using the code in NoteSynth.c
     *
     * To insert a note, you need to call the function provided
     * in NoteSynth.c:
     *
     * playlist_head=playlist_insert(freq,bar,index);
     *
     * playlist_head is a GLOBAL variable declared in NoteSynth.c
     * precisely for this purpose. Don't worry about intializing
     * it. It's set to NULL.
     *
     * playlist_insert() takes the frequency, bar, and index, and
     * adds the note to the the *end* of the list - so notes
     * have to be added in order - hence the in-order traversal
     * this function has to do.
     */
}

void BST_inOrder(BST_Node *root, int depth)
{
    // Check if tree is empty.
    if (root == NULL) return;
    int temp = depth + 1;
    // Apply in-order traversal.
    BST_inOrder(root->left, temp);
    // Print data.
    printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n", depth, root->bar, root->index, root->freq);
    BST_inOrder(root->right, temp);
    /*
     * This function performs an in-order traversal of the BST
     * and prints out the note information for each note
     * using this print statement:
     *
     *  printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n",...);
     *
     * Obviously, you must provide the bar, index, and frequency
     * of the note that needs to be printed to complete the
     * statement - we're just giving you the formatting string.
     *
     * The depth value is increased by 1 for each recursive call
     * so when you print, you can see at what level each node
     * is located! (this should help you debug your code by
     * making it easier to check the shape of your BST).
     */
}

void BST_preOrder(BST_Node *root, int depth)
{
    // Check if tree is empty.
    if (root == NULL) return;
    // Print data.
    int temp = depth + 1;
    printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n", depth, root->bar, root->index, root->freq);
    // Apply pre-order traversal.
    BST_preOrder(root->left, temp);
    BST_preOrder(root->right, temp);
    /*
     * This function performs an pre-order traversal of the BST
     * and prints out the note information for each note
     * using this print statement:
     *
     *  printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n",...);
     *
     * Obviously, you must provide the bar, index, and frequency
     * of the note that needs to be printed to complete the
     * statement - we're just giving you the formatting string.
     *
     * The depth value is increased by 1 for each recursive call
     * so when you print, you can see at what level each node
     * is located! (this should help you debug your code by
     * making it easier to check the shape of your BST).
     */
}

void BST_postOrder(BST_Node *root,int depth)
{
    // Check if tree is empty.
    if (root == NULL) return;
    int temp = depth + 1;
    // Apply post-order traversal.
    BST_postOrder(root->left, temp);
    BST_postOrder(root->right, temp);
    // Print data.
    printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n", depth, root->bar, root->index, root->freq);
    /*
     * This function performs an post-order traversal of the BST
     * and prints out the note information for each note
     * using this print statement:
     *
     *  printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n",...);
     *
     * Obviously, you must provide the bar, index, and frequency
     * of the note that needs to be printed to complete the
     * statement - we're just giving you the formatting string.
     *
     * The depth value is increased by 1 for each recursive call
     * so when you print, you can see at what level each node
     * is located! (this should help you debug your code by
     * making it easier to check the shape of your BST).
     */
}

void delete_BST(BST_Node *root)
{
    // Check if root is NULL.
    if (root == NULL) return;
    // Traverse all the way to the leftmost child in the BST.
    delete_BST(root->left);
    // Traverse all the way to the lowest level in the BST.
    delete_BST(root->right);
    // Removing all links to children.
    root->right = NULL;
    root->left = NULL;
    // Free the node in the lowest level.
    free (root);
    /*
     * This function deletes the BST and frees all memory used for
     * nodes in it. Recall that there is a specific order in which
     * this needs to be done! (consult the Unit 4 notes as needed)
     */
}

double name_to_frequency(char note[5])
{
    // Loop through note_names.
    for (int i = 0; i < 100; i++){
        // Check if entry matches parameter, and return corresponding frequency.
        if (strcmp(note, note_names[i]) == 0) return note_freq[i];
    }
    // Return -1.0 if no entry matches parameter.
    return -1.0;
    /*
     * This function traverses note_names, finds the entry that
     * matches note (our input parameter) and returns the
     * corresponding frequency of that note from note_freq.
     *
     * If the input parameter does not match any entry in note_names,
     * then this function returns -1.0.
     */
}

void BST_shiftFreq(BST_Node *root, char note_src[5], char note_dst[5])
{
    // Check if tree is empty.
    if (root == NULL) return;
    // Apply in-order travrsal.
    BST_shiftFreq(root->left, note_src, note_dst);
    double freq_new = name_to_frequency(note_dst);
    // Check if notes (and therefore frequencies associated with them) are valid. Procced to replace if valid.
    if (root->freq == name_to_frequency(note_src) && freq_new != -1.0) root->freq = freq_new;
    BST_shiftFreq(root->right, note_src, note_dst);
    /*
     * This function goes over the entries in the BST, finds notes
     * corresponding to note_src (which is a text string describing
     * a note's name in the musical scale), and shifts those notes
     * to the frequency of note_dst (another text string with a note
     * name). Effectively, it replaces one particular type of note
     * by another all through the song.
     *
     * The note names are in either 2 or 3 characters long, and
     * you can see all of them in the file 'note_frequencies.txt'
     *
     * Happily, you *DON'T HAVE TO READ THAT FILE YOURSELVES*, the
     * NoteSynth code has already done that, and it gives you
     * two GLOBAL arrays:
     *
     * char note_names[100][5] - an array of 100 rows, for strings
     *                           with at most 5 characters each.
     *                  Each note name is one row in this
     *                  array ad the notes are sorted
     *                  by frequency.
     *                  There are 100 notes in all
     * double note_freq[100]   - An array of double precision
     *                  floating point numbers with the
     *                  frequencies for each of the
     *                  notes in note_names[][].
     *                  note_freq[i] has the frequency
     *                  for the note whose name is
     *                  stored in note_names[i][]
     *
     * The user doesn't know about frequencies, so they will just
     * give you the note names they want. If the user sends a
     * string that doesn't correspond to a valid note name, for
     * either the note_src[] or the note_dst[], then this
     * function should do nothing.
     *
     * Expected result: All notes in the BST whose frequency
     * corresponds to the frequency of note_src, should have
     * their frequency changed to that of note_dst.
     */
}

/********************************************************************************************
 *      Add any helper functions you need for implementing BST_harmonize() just below this
 * comment block, and aboce BST_Harmonize itself!
 * ******************************************************************************************/

double harmony_freq(double freq, int semitones)
{
    // Loop through note_freq.
    for (int i = 0; i < 100; i++){
        // Check if entry matches parameter.
        if (note_freq[i] == freq){
            int shift = i + semitones;
            // Check if shifted index is within bounds, and return the entry
            // at the shifted index if it is within bounds.
            if (0 <= shift && shift < 100) return note_freq[shift];
        }
    }
    // Return -1.0 if no entry matches parameter or if shifted index is out of bounds.
    return -1.0;
    /*
     * This function traverses note_freq, finds the entry that
     * matches freq (lets say at index i), and returns the frequency
     * at index (i + semitones) of note_freq.
     *
     * If the input parameter freq does not match any entry in note_names or
     * if the index of new frequency to be returned is out of bounds, return -1.0.
     */
}

// Create global pointer to a linked list that will store a list of
// harmony_notes that will be added to the tree based on the input
// parameters in BST_harmmonize.
BST_Node *Harmony_notes = NULL;

void Create_list(BST_Node *root, int semitones, double time_shift)
{
    // Check if tree is empty.
    if (root == NULL) return;
    // Apply pre-order traversal.
    // Define the data for the possible new note.
    double new_freq = harmony_freq(root->freq, semitones);
    double new_index = root->index + time_shift;
    // Check if new data satisfies conditions.
    if (new_freq != -1 && new_index>=0 && new_index < 1)
    {
        // Create a new note.
        BST_Node *new_note = newBST_Node(new_freq, root->bar, new_index);
        // Link new note to linked list.
        new_note->right = Harmony_notes;
        // Change the head of the linked list.
        Harmony_notes = new_note;
    }
    Create_list(root->left, semitones, time_shift);
    Create_list(root->right, semitones, time_shift);
    /*
     * This function traverses the tree and finds the notes that satisfy
     * the conditions to be added in the tree according to BST_harmonize.
     * It then stores the modified notes to be added into the tree in a
     * global linked linked list Harmony_notes.
     */
}

BST_Node *BST_harmonize(BST_Node *root, int semitones, double time_shift)
{
    // Creating the linked list of notes to be inserted.
    Create_list(root, semitones, time_shift);
    // Declaring and initialising a pointer to the head of the linked list.
    BST_Node *traversal = NULL;
    traversal = Harmony_notes;
    // Looping over the linked list.
    while(traversal != NULL){
        // Storing the pointer to successor of traversal.
        BST_Node *successor = traversal->right;
        // Removing the link to the right child, so that traversal
        // can be inserted as a note into the tree.
        traversal->right = NULL;
        // Checking if note with duplicate key exists.
        while (BST_search(root, traversal->bar, traversal->index) != NULL){
            // Shifting the index and also the key, so that we can
            // insert it into the tree.
            // Making sure index shift does not cause inedx to become out of bounds.
            if (traversal->index >= 0.5) traversal->index -= 1e-11 * 13 * traversal->freq;
            else traversal->index += 1e-11 * 17 * traversal->freq;
            traversal->key = (10.0 * traversal->bar) + traversal->index;
        }
        // Inserting the note into the tree.
        root = BST_insert(root, traversal);
        traversal = successor;
    }
    // Reset global variable for reuse.
    Harmony_notes = NULL;
    // Return root.
    return root;
    /* Let's play with notes, because we can.
     *
     * This function traverses the BST, and for each existing
     * note, inserts a new, modified note (i.e. it will add sounds
     * to an already existing song, based on the notes it already has)
     *
     * The new note has the followin properties:
     * - The frequency is shifted by the specified number of semitones
     *   (A semitone is the difference between one note and the
     *    immediately next one in the musical scale - ot what is the
     *    same, the difference in pitch between a white key and the
     *    black key immediately next to it in a piano)
     * - It plays in the same *bar* as the original note
     * - But its *index* is shifted by the specified time_shift
     *   (this value is between 0 and 1, but you have to check
     *    that the final index remains between 0 and 1)
     *
     * Both the 'semitones' and 'time_shift' parameter can be
     * positive or negative. A typical value for semitones
     * could be 4 or 7, corresponding to musical 3rds or
     * musical 5ths - this should produce some interesting
     * harmony! but you can play with this function and try
     * various things for fun.
     *
     * In practice, figuring out the frequency of the note
     * you have to insert is easy. For instance, suppose
     * you have an existing note in  the BST with
     *
     * freq=440.0, at bar=10, index=.25
     *
     * Now suppose the user specified
     *
     * semitones=4
     * time_shift=.1
     *
     * Then you go to the note_freq[] array, find the index
     * of the entry for frequency 440.0 (let's say it's
     * j), then go to note_freq[j+4] to find the frequency
     * of the note you need to add.
     *
     * NOTE: If the value of  j+semitones  is < 0 or > 99
     *       then there is no note with the frequency you
     *       want. In that case you don't insert a new
     *       note.
     *
     * You then add a new note with that frequency at
     * bar=10 (same bar!)
     * index=.25 + .1  (the original index plus the time_shift)
     *
     * NOTE: If the resulting index is less than 0, or >= 1,
     *       then you DO NOT insert the new note.
     *
     * This function is crunchy - and if you don't think it
     * through before you start implementing it you'll run into
     * all kinds of trouble.
     *
     * This is the problem solving exercise for A2, so don't
     * look for people on Piazza to give you answers, or tell you
     * what to do, or verify you're doing the right thing.
     *
     * It's up to you how to solve this, and if you want an opinion,
     * you can come to visit us during office hours!
     *
     * Expected result: The BST will have about twice as many notes
     *   as before, and the new notes are shifted in pitch and
     *   in time as specified by the parameters.
     */
}
