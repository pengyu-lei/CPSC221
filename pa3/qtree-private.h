/**
 * @file qtree-private.h
 * @description student declaration of private QTree functions
 *              CPSC 221 PA3
 *
 *              SUBMIT THIS FILE.
 * 
 *				Simply declare your function prototypes here.
 *              No other scaffolding is necessary.
 */

// begin your declarations below

RGBAPixel calculateAvg(Node* node);
void RenderHelper(PNG& img, Node* subroot, int scale) const;
void ClearHelper(Node* subroot);
Node* CopyHelper(Node* other);
void PruneHelper(Node* subroot, double tolerance);
bool ShouldPrune(RGBAPixel rootAvgColor, Node* subroot, double tolerance);
void FlipHelper(Node* subroot);
void RotateHelper(Node* subroot);
void RotateSwap(Node* subroot);