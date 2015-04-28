#ifndef SOURCEFUNCTION_H
#define SOURCEFUNCTION_H

#include <iostream> 
#include <Eigen/Dense>

using namespace std; 

enum SHAPE { cylinder };

class SourceFunction
{
    const double _baseSpeed; 
    const SHAPE _shape; 
    const Eigen::MatrixXd * _g; 

    double _localAbsMax; 

    public : 

    const int maxTimeStep; 
        
    SourceFunction(const double bs, const SHAPE s, const Eigen::MatrixXd * g) : 
        _baseSpeed(bs), 
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

    ~SourceFunction()
    {
        if (_g) 
            delete _g; 
    }

    const char * getShapeName() const
    {
        switch (_shape) 
        {
            case cylinder : return "2D cylinder"; break;
        }

        return NULL;
    }

    inline void computeLocalAbsMax()
    {
        _localAbsMax = max(_g->maxCoeff(),-1.0*_g->minCoeff()); 
    }


    double getBaseSpeed() const 
    {
        return _baseSpeed; 
    }

    inline double getgx(int t) const
    {
        return (*_g)(t,0); 
    }

    inline double getgy(int t) const
    {
        return (*_g)(t,1); 
    }

    inline double getgz(int t) const
    {
        return (*_g)(t,2); 
    }

    inline double getmax() const
    {
        return _localAbsMax; 
    }

};


#endif
