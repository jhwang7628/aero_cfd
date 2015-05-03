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

    cout << "maxTimeStep = " << maxTimeStep << endl;
    computeLocalAbsMax();
}

SourceFunction::~SourceFunction()
{
    if (_g) 
        delete _g; 
}

Eigen::MatrixXd * SourceFunction::postProcessG(const Eigen::MatrixXd *g) const 
{

    Eigen::MatrixXd * gProcessed = new Eigen::MatrixXd(); 

    gProcessed->setZero(g->rows()*PARAMETERS::UPSAMPLE_RATIO, g->cols()); 
    for (int ii=0; ii<g->rows(); ii++) 
    {
        double count = 0; 
        for (int jj=ii*PARAMETERS::UPSAMPLE_RATIO; jj<(ii+1)*PARAMETERS::UPSAMPLE_RATIO; jj++) 
        {
            double alpha = count/(double)PARAMETERS::UPSAMPLE_RATIO; 

            int thisTS = ii;
            int nextTS = ii+1; 
            if (ii+1 == g->rows()) 
                nextTS = 0; // wrap-around

            gProcessed->row(jj) = g->row(thisTS)*(1.0-alpha) + g->row(nextTS)*alpha;  // linterp

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

