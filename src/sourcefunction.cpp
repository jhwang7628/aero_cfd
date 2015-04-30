#include "sourcefunction.h"
#include "parameters.h"

SourceFunction::SourceFunction(const double bs, const SHAPE s, const Eigen::MatrixXd * g) : _baseSpeed(bs), 
            _shape(s), 
            _g(postProcessG(g)), 
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

Eigen::MatrixXd * SourceFunction::postProcessG(const Eigen::MatrixXd *g)
{

    Eigen::MatrixXd * gProcessed = new Eigen::MatrixXd(); 
    gProcessed->setZero(g->rows()*UPSAMPLE_RATIO, g->cols()); 
    for (int ii=0; ii<g->rows(); ii++) 
    {
        double count = 0; 
        for (int jj=ii*UPSAMPLE_RATIO; jj<(ii+1)*UPSAMPLE_RATIO; jj++) 
        {
            double alpha = count/(double)UPSAMPLE_RATIO; 

            int thisTS = ii;
            int nextTS = ii+1; 
            if (ii+1 == g->rows()) 
                nextTS = 0; // wrap-around

            gProcessed->row(jj) = g->row(thisTS)*alpha + g->row(nextTS)*(1.0-alpha);  // linterp

            count += 1.0; 
        }
    }

    return gProcessed; 

}


const char * SourceFunction::getShapeName() const
{
    switch (_shape) 
    {
        case cylinder : return "2D cylinder"; break;
    }

    return NULL;
}

