#ifndef SOURCEFUNCTION_H
#define SOURCEFUNCTION_H

#include <iostream> 
#include <Eigen/Dense>

using namespace std; 

enum SHAPE { cylinder, square, sword_aniso };

class SourceFunction
{
    const double _baseSpeed; 
    const SHAPE _shape; 
    const Eigen::MatrixXd * _g;  // N-by-3 matrix
    const int _textureIndex;  // identify which texture is this

    double _localAbsMax; 

    public : 

    const int maxTimeStep; 
        
    SourceFunction(const double bs, const SHAPE s, const Eigen::MatrixXd * g, const int textureIndex); 

    ~SourceFunction(); 


    double getBaseSpeed() const
    {
        return _baseSpeed; 
    }

    int getTextureIndex() const 
    {
        return _textureIndex; 
    }

    Eigen::MatrixXd * postProcessG(const Eigen::MatrixXd * g) const;

    const char * getShapeName() const; 


    inline void computeLocalAbsMax()
    {
        _localAbsMax = max(_g->maxCoeff(),-1.0*_g->minCoeff()); 
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
