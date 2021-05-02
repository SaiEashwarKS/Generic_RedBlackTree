#include "rbt.h"
void fuc()
{
    if (x == root)
        // Reached root
        return;

    auto *sibling = x->sibling(), *parent = x->parent;
    if (sibling == NULL)
    {
        // No sibiling, double black pushed up
        fixDoubleBlack(parent);
    }
    else
    {
        if (sibling->color == RED)
        {
            // Sibling red
            parent->color = RED;
            sibling->color = BLACK;
            if (sibling->isOnLeft())
            {
                // left case
                rightRotate(parent);
            }
            else
            {
                // right case
                leftRotate(parent);
            }
            fixDoubleBlack(x);
        }
        else
        {
            // Sibling black
            if (sibling->hasRedChild())
            {
                // at least 1 red children
                if (sibling->left != NULL && sibling->left->color == RED)
                {
                    if (sibling->isOnLeft())
                    {
                        // left left
                        sibling->left->color = sibling->color;
                        sibling->color = parent->color;
                        rightRotate(parent);
                    }
                    else
                    {
                        // right left
                        sibling->left->color = parent->color;
                        rightRotate(sibling);
                        leftRotate(parent);
                    }
                }
                else
                {
                    if (sibling->isOnLeft())
                    {
                        // left right
                        sibling->right->color = parent->color;
                        leftRotate(sibling);
                        rightRotate(parent);
                    }
                    else
                    {
                        // right right
                        sibling->right->color = sibling->color;
                        sibling->color = parent->color;
                        leftRotate(parent);
                    }
                }
                parent->color = BLACK;
            }
            else
            {
                // 2 black children
                sibling->color = RED;
                if (parent->color == BLACK)
                {
                    fixDoubleBlack(parent);
                }
                else
                {
                    parent->color = BLACK;
                }
            }
        }
    }
}