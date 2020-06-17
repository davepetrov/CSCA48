#include "BSTs_1006206428.c"
#include "LUDOTest_Basic.c"

int main() {
    read_note_table();
    BST_Node * root = NULL, * newNode, * temp;

    printf("--------------- NULL or 1 Node ---------------\n");
    pointerEqual(BST_search(root, 1, 1), NULL, 1, "Search empty tree");

    // insert into null BST
    newNode = newBST_Node(880., 5, 0.5);
    floatEqual(newNode -> key, 50.5, 2, "Node create correctly");
    root = BST_insert(root, newNode);
    floatEqual(root -> key, 50.5, 3, "Root node inserted correctly");

    // remove from a one node BST
    root = BST_delete(root, 0, 0);
    floatEqual(root -> key, 50.5, 4, "Delete non-existing node");
    root = BST_delete(root, 5, 0.5);
    pointerEqual(root, NULL, 5, "Root node deleted correctly");

    // adding some data
    root = BST_insert(root, newBST_Node(880., 5, 0.50)); // A5
    // left tree
    root = BST_insert(root, newBST_Node(830.61, 3, 0.95)); // G5#
    root = BST_insert(root, newBST_Node(739.99, 0, 0.01)); // F5#
    root = BST_insert(root, newBST_Node(16.35, 0, 0.00)); // C0
    root = BST_insert(root, newBST_Node(783.99, 1, 0.05)); // G5
    root = BST_insert(root, newBST_Node(783.99, 0, 0.95)); // G5
    root = BST_insert(root, newBST_Node(783.99, 0, 0.85)); // G5
    root = BST_insert(root, newBST_Node(783.99, 5, 0.05)); // G5
    // right tree
    root = BST_insert(root, newBST_Node(932.33, 13, 0.80)); // A5#
    root = BST_insert(root, newBST_Node(978.77, 6, 0.40)); // B5
    root = BST_insert(root, newBST_Node(978.77, 10, 0.35)); // B5
    root = BST_insert(root, newBST_Node(1108.73, 19, 0.60)); // C6#
    root = BST_insert(root, newBST_Node(1046.50, 18, 0.50)); // C6
    root = BST_insert(root, newBST_Node(1046.50, 18, 0.65)); // C6
    root = BST_insert(root, newBST_Node(1046.50, 19, 0.20)); // C6
    root = BST_insert(root, newBST_Node(1046.50, 17, 0.99)); // C6
    root = BST_insert(root, newBST_Node(4978.03, 25, 0.95)); // D8#
    root = BST_insert(root, newBST_Node(1244.51, 22, 0.70)); // D6#
    root = BST_insert(root, newBST_Node(1244.51, 22, 0.65)); // D6#
    root = BST_insert(root, newBST_Node(4978.03, 26, 0.00)); // D8#

    // Check of the nodes are inserted correctly
    printf("\n--------------- Check insert correctness ---------------\n");
    floatEqual(root -> key, 50.5, 6, "Check insert");
    floatEqual(root -> left -> key, 30.95, 7, "Check insert");
    floatEqual(root -> left -> left -> key, 0.01, 8, "Check insert");
    floatEqual(root -> left -> left -> left -> key, 0.00, 9, "Check insert");
    floatEqual(root -> left -> left -> right -> key, 10.05, 10, "Check insert");
    floatEqual(root -> left -> left -> right -> left -> key, 0.95, 11, "Check insert");
    floatEqual(root -> left -> left -> right -> left -> left -> key, 0.85, 12, "Check insert");
    floatEqual(root -> left -> right -> key, 50.05, 13, "Check insert");
    floatEqual(root -> right -> key, 130.80, 14, "Check insert");
    floatEqual(root -> right -> left -> key, 60.40, 15, "Check insert");
    floatEqual(root -> right -> left -> right -> key, 100.35, 16, "Check insert");
    floatEqual(root -> right -> right -> key, 190.60, 17, "Check insert");
    floatEqual(root -> right -> right -> left -> key, 180.50, 18, "Check insert");
    floatEqual(root -> right -> right -> left -> left -> key, 170.99, 19, "Check insert");
    floatEqual(root -> right -> right -> left -> right -> key, 180.65, 20, "Check insert");
    floatEqual(root -> right -> right -> left -> right -> right -> key, 190.20, 21, "Check insert");
    floatEqual(root -> right -> right -> right -> key, 250.95, 22, "Check insert");
    floatEqual(root -> right -> right -> right -> left -> key, 220.70, 23, "Check insert");
    floatEqual(root -> right -> right -> right -> left -> left -> key, 220.65, 24, "Check insert");
    floatEqual(root -> right -> right -> right -> right -> key, 260.00, 25, "Check insert");

    printf("\n--------------- Check if trees matches ---------------\n");
    printf("\nPre-order:\n");
    BST_preOrder(root, 0);
    printf("\n");
    printf("In-order:\n");
    BST_inOrder(root, 0);
    printf("\n");
    printf("Post-order:\n");
    BST_postOrder(root, 0);
    printf("\n--------------- Check if trees matches ---------------\n\n");

    // Check searching
    printf("\n--------------- Check searching ---------------\n");
    pointerEqual(BST_search(root, 100, 0.5), NULL, 26, "Search non-existing node");
    pointerEqual(BST_search(root, 5, 0.5), root, 27, "Searching root");
    pointerEqual(BST_search(root, 0, 0.01), root -> left -> left, 28, "Ordinary search");
    pointerEqual(BST_search(root, 18, 0.65), root -> right -> right -> left -> right, 29, "Ordinary search");
    pointerEqual(BST_search(root, 5, 0.05), root -> left -> right, 30, "Ordinary search");

    // Check deletiion
    printf("\n--------------- Check deletion ---------------\n");
    root = BST_delete(root, 10, 0.35);
    pointerEqual(root -> right -> left -> right, NULL, 31, "Delete leaf node");
    pointerEqual(root -> right -> left -> left, NULL, 32, "Delete leaf node, make sure parent other pointer wasn't affected");
    floatEqual(root -> right -> left -> key, 60.40, 33, "Delete leaf node, make sure parent key wasn't affected");
    root = BST_delete(root, 1, 0.05);
    floatEqual(root -> left -> left -> key, 0.01, 34, "One child, check parent key wasn't affected");
    floatEqual(root -> left -> left -> left -> key, 0.00, 35, "One child, make sure the other pointer for the parent wasn't affected");
    floatEqual(root -> left -> left -> right -> key, 0.95, 36, "One child, make sure tail followed up");
    floatEqual(root -> left -> left -> right -> left -> key, 0.85, 37, "One child, make sure tail followed up");

    // delete with two children
    printf("\nTesting delete node with 2 children, expecting you to replace with smallest of right subtree\n");
    root = BST_delete(root, 19, 0.60);
    temp = root -> right -> right;
    floatEqual(temp -> key, 220.65, 38, "Check of the successor key has been copied");
    floatEqual(temp -> bar * 10.0 + temp -> index, 220.65, 39, "Check of the successor bar & index had been copied");
    floatEqual(temp -> freq, 1244.51, 40, "Check of the successor freq has been copied");
    floatEqual(temp -> right -> key, 250.95, 41, "Check if following remain unchanged");
    floatEqual(temp -> right -> right -> key, 260.00, 42, "Check if following remain unchanged");
    floatEqual(temp -> right -> left -> key, 220.70, 43, "Check if following remain unchanged");
    pointerEqual(temp -> right -> left -> left, NULL, 44, "Check pointer of parent of successor have been updated");
    pointerEqual(temp -> left, BST_search(root, 18, 0.50), 45, "Check left side remain unchanged");

    // Check shift
    printf("\n--------------- Check shiftFreq ---------------\n");
    root = BST_insert(root, newBST_Node(1108.73, 16, 0.75));
    BST_shiftFreq(root, "C6", "E6");
    floatEqual(root -> right -> right -> left -> freq, 1318.51, 46, "Check C6 update");
    floatEqual(root -> right -> right -> left -> left -> freq, 1318.51, 47, "Check C6 update");
    floatEqual(root -> right -> right -> left -> right -> freq, 1318.51, 48, "Check C6 update");
    floatEqual(root -> right -> right -> left -> right -> right -> freq, 1318.51, 49, "Check C6 update");
    floatEqual(root -> right -> right -> left -> left -> left -> freq, 1108.73, 50, "C6# != C6, shouldn't be updated");

    //Check harmonize
    root = BST_harmonize(root, 1, 0.99);
    floatEqual(root -> left -> left -> right -> right -> key, 0.99, 51, "One node of bar 0 index 0.99 should be added");
    floatEqual(root -> left -> left -> right -> right -> freq, 17.32, 52, "Freq should be 17.32 or C0#");

    printf("Your code would prompt you that duplicate node requested IF you used BST_insert to insert the new node:\n");
    root = BST_harmonize(root, -1, -0.99);
    floatEqual(root -> right -> right -> left -> left -> left -> right -> key, 170.00, 53, "One node of bar 17 index 0 should be added");
    floatEqual(root -> right -> right -> left -> left -> left -> right -> freq, 1244.51, 54, "Freq should be 1244.51 or D6#");

    printf("\n--------------- Check if trees matches ---------------\n");
    printf("\nPre-order:\n");
    BST_preOrder(root, 0);
    printf("\n");
    printf("In-order:\n");
    BST_inOrder(root, 0);
    printf("\n");
    printf("Post-order:\n");
    BST_postOrder(root, 0);
    printf("\n--------------- Check if trees matches ---------------\n\n");

    printResult();
    return 0;
}
