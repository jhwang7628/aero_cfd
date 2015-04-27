#include <iostream> 
#include <Eigen/Dense>

enum SHAPE { cylinder };

class SourceFunction
{
    const double _baseSpeed; 
    const SHAPE _shape; 
    const Eigen::MatrixXd * _g; 

    public : 
        
    SourceFunction(const double bs, const SHAPE s, const Eigen::MatrixXd * g) : _baseSpeed(bs), _shape(s), _g(g)
    {
        cout << "Source Function initialized for shape "; 
        switch (_shape)
        {
            case cylinder : cout << "\"2D cylinder\"." << endl; break;
        }

    }

    ~SourceFunction()
    {
        if (_g) 
            delete _g; 
    }

};
