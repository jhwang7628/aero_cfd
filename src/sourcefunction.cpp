#include "sourcefunction.h"

SourceFunction::SourceFunction(const double bs, const SHAPE s, const Eigen::MatrixXd * g) : _baseSpeed(bs), 
            _shape(s), 
            _g(g), 
            maxTimeStep(_g->rows())
{
    cout << "New source function initialized for shape "; 
    switch (_shape)
    {
        case cylinder : printf("\"%s\"\n", getShapeName());
                        break;
    }
    computeLocalAbsMax();
}

SourceFunction::~SourceFunction()
{
    if (_g) 
        delete _g; 
}

const char * SourceFunction::getShapeName() const
{
    switch (_shape) 
    {
        case cylinder : return "2D cylinder"; break;
    }

    return NULL;
}

