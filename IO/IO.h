#ifndef IO_H
#define IO_H

#include <iostream> 
#include <fstream> 
#include <Eigen/Dense> 
#include <assert.h> 
#include <cstdio>
#include <dirent.h>

#include <vector>

#define BUFFER_SIZE 500

using namespace std; 


typedef enum {
    BINARY, 
    BINARY_V3, // only implemented for reading
    ASCII
} FileType;

class IO { 

    public: 
        // Write Eigen matrix data to a binary file. 
        // Format 
        static void writeMatrixXd( const Eigen::MatrixXd &data, const char *filename, FileType x ) 
        { 

            int Nrow = (int) data.rows(); 
            int Ncol = (int) data.cols(); 

            switch (x) {

                case BINARY :
                    {
                        cout << "Write data in BINARY format to file : " << filename << endl;
                        ofstream of1(filename, ios::out | ios::binary);

                        if (!of1) 
                        {
                            cerr << "** file I/O (O) problem. Returning" << endl; 
                            return;
                        }

                        cout << " - Data Dimension: " << Nrow << " x " <<  Ncol << endl; 
                        of1.write((char *) &Nrow, sizeof(int));
                        of1.write((char *) &Ncol, sizeof(int)); 


                        cout << " - Progress: " << endl; 
                        cout << "     " << "0 % "; 
                        for (int ii=0; ii<Nrow; ii++) 
                        {
                            if (ii%50 ==0)
                            {
                                cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
                                cout << "     " << (double)ii/(double)Nrow*100.0 << " % "; 
                            }
                            for (int jj=0; jj<Ncol; jj++) 
                                of1.write((char *) &data(ii,jj), sizeof(double));
                        }
                        cout << endl; 

                        of1.close(); 
                        break;

                    }
                case BINARY_V3 : 
                    {
                        cout << "Write data in BINARY_V3 format to file : " << filename << endl;
                        ofstream of1(filename, ios::out | ios::binary);

                        if (!of1) 
                        {
                            cerr << "** file I/O (O) problem. Returning" << endl; 
                            return;
                        }

                        int Nactual = Ncol / 3; 
                        cout << " - Data Dimension (V3): " << Nrow << " x " <<  Nactual << endl; 
                        of1.write((char *) &Nrow   , sizeof(int));
                        of1.write((char *) &Nactual, sizeof(int)); 


                        cout << " - Progress: " << endl; 
                        cout << "     " << "0 % "; 
                        for (int ii=0; ii<Nrow; ii++) 
                        {
                            if (ii%50 ==0)
                            {
                                cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
                                cout << "     " << (double)ii/(double)Nrow*100.0 << " % "; 
                            }
                            for (int jj=0; jj<Ncol; jj++) 
                                of1.write((char *) &data(ii,jj), sizeof(double));
                        }
                        cout << endl; 

                        of1.close(); 
                        break;
                    }
                case ASCII : 
                    {
                        FILE *fs1;
                        fs1 = fopen(filename ,"w"); 
                        cout << "Write data in ASCII format to file : " << filename << endl;

                        cout << " - Progress: " << endl; 
                        cout << "     " << "0 % "; 
                        for (int ii=0; ii<Nrow; ii++) 
                        {
                            if (ii%50 ==0)
                            {
                                cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
                                cout << "     " << (double)ii/(double)Nrow*100.0 << " % "; 
                            }
                            for (int jj=0; jj<Ncol; jj++)
                                fprintf(fs1, "%.9f ", data(ii,jj));

                            fprintf(fs1, "\n");
                        }
                        fclose(fs1);
                        cout << endl; 
                        break; 
                    }
            }
        }

        static void readMatrixXd( Eigen::MatrixXd &matout2D, const char *filename, FileType x ) 
        {
            switch (x) {

                case BINARY :
                    {

                        cout << "Read BINARY 2D data : " << filename << endl;

                        ifstream file(filename, ios::in | ios::binary | ios::ate); 

                        if (!file)  
                        {
                            cerr << "** Cannot find file " << filename << "." << endl; 
                        }


                        streampos size = file.tellg(); 
                        cout << " - Queried file size : " << size << endl; 

                        int Nrow, Ncol;  

                        file.seekg (0, ios::beg); 
                        file.read((char*)&Nrow, sizeof(int)); 
                        file.read((char*)&Ncol, sizeof(int)); 

                        // streampos size_left = (int)size - 2*sizeof(int); 

                        matout2D.resize(Nrow, Ncol); 

                        cout << " - progress: " << endl; 
                        cout << "     0 %";
                        for (int ii=0; ii<Nrow; ii++)
                        {
                            if ( ii % 50 == 0 )
                            {
                                cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b"
                                     << "     " << (double)ii/(double)Nrow*100 << " % ";
                            }
                            for (int jj=0; jj<Ncol; jj++) 
                                file.read((char*)&matout2D(ii,jj), sizeof(double)); 
                        }
                        cout << endl; 

                        file.close(); 
                        cout << " - Data read in has dimension = (" << Nrow << ", " << Ncol << ")" << endl;

                        break; 
                    }

                case BINARY_V3 : 
                    {
                        cout << "Read BINARY Vector3 data : " << filename << endl;

                        ifstream file(filename, ios::in | ios::binary | ios::ate); 

                        if (!file)  
                        {
                            cerr << "cannot find file " << filename << "." << endl; 
                        }


                        streampos size = file.tellg(); 
                        cout << " - Queried file size : " << size << endl; 

                        int Nrow, Ncol;  

                        file.seekg (0, ios::beg); 
                        file.read((char*)&Nrow, sizeof(int)); 
                        file.read((char*)&Ncol, sizeof(int)); 

                        // streampos size_left = (int)size - 2*sizeof(int); 

                        matout2D.resize(Nrow, Ncol*3); 

                        cout << " - progress: " << endl; 
                        cout << "     0 %";
                        for (int ii=0; ii<Nrow; ii++)
                        {
                            if ( ii % 50 == 0 )
                            {
                                cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b" 
                                     << "     " << (double)ii/(double)Nrow*100 << " % ";
                            }
                            for (int jj=0; jj<Ncol*3; jj++) 
                                file.read((char*)&matout2D(ii,jj), sizeof(double)); 
                        }
                        cout << endl; 

                        file.close(); 
                        cout << " - Data read in has dimension = (" << Nrow << ", " << Ncol << "*3)" << endl;

                        break; 
                    }
                case ASCII :
                    {
                        cout << "Read ASCII data : " << filename << endl; 

                        ifstream ifs(filename); 

                        if (!ifs) 
                        {
                            cerr << "Cannot open file " << filename << ". Returning. " << endl; 
                            return; 
                        }

                        string line; 
                        int Nrow=0, Ncol; 
                        while (getline(ifs, line))
                        {
                            Nrow ++; 

                            //cout << "Nrow = " << Nrow << endl; 

                            istringstream iss(line); 

                            vector<double> tmp; 
                            double buffer; 

                            Ncol = 0; 
                            while (iss >> buffer)
                            {
                                Ncol ++; 
                                tmp.push_back(buffer); 
                            }

                            // resize and push the vector content into eigen
                            // matrices
                            matout2D.conservativeResize(Nrow, Ncol); 
                            for (unsigned int ii=0; ii<tmp.size(); ii++) 
                            {
                                matout2D(Nrow-1, ii) = tmp[ii]; 
                            }

                        }

                        ifs.close(); 

                        break; 


                    }
            }

            cout << "Read complete." << endl; 

        }

        /**
         * Discrete read the ascii files. 
         * it is usually useful to skip a couple of lines of headers, 
         * and then discretely pick columns for reading. This method implements
         * this functionality. 
         *
         * rows: an integer specifying number of lines that will be SKIPPED. 
         * cols: a std vector that will be PICKED. (don't need to be ordered)
         *       if cols is a zero-vector, then all cols will be read. 
         *
         * Note: 
         *  1. rows is 1-based (specify size); cols is 0-based (specify position). 
         *  2. if cols contains repeated values it will only be read once. 
         */ 
        static void readMatrixXd_discrete_ASCII(Eigen::MatrixXd &matout2D, const char* filename, 
                                      int rows, vector<int> cols)
        {
            assert (rows >= 0); 

            ifstream ifs(filename); 

            if (!ifs) 
            {
                cerr << "** Cannot open file " << filename << ". Returning. " << endl; 
                return; 
            }




            cout << "Read ASCII data discretely : " << filename << endl << endl; 

            cout << "-------------------------------------------------- " << endl; 
            cout << "The following #rows from the file will be SKIPPED : " << endl; 
            cout << rows << endl; 
            cout << "-------------------------------------------------- " << endl; 
            cout << "The following columns from the file will be READ : " << endl; 
            for (unsigned int ii=0; ii<cols.size(); ii++)
                cout << cols[ii] << " "; 
            cout << endl; 
            cout << "-------------------------------------------------- " << endl; 


            string buffer; 
            for (int ii=0; ii<rows; ii++)
            {
                if (!getline(ifs, buffer))
                {
                    cerr << "** Oops, skipping too many rows?" << endl; 
                    return; 
                }
            }

            int Nrow=0, Ncol;  
            string line; 
            while (getline(ifs, line))
            {
                Nrow ++; 

                istringstream iss(line); 

                vector<double> tmp; 
                double buffer; 


                int count = 0; 
                Ncol = 0; 
                while (iss >> buffer)
                {
                    if (cols.size() > 0)
                    {
                        // simple linear search to check
                        for (unsigned int jj=0; jj<cols.size(); jj++) 
                        {
                            if (count == cols[jj]) 
                            {
                                Ncol ++; 
                                tmp.push_back(buffer); 
                                break; 
                            }
                        }
                    }
                    else  // read all
                    {
                        Ncol ++; 
                        tmp.push_back(buffer); 
                    }
                    count ++; 
                }

                // resize and push the vector content into eigen
                // matrices
                matout2D.conservativeResize(Nrow, Ncol); 
                for (unsigned int ii=0; ii<tmp.size(); ii++) 
                {
                    matout2D(Nrow-1, ii) = tmp[ii]; 
                }

            }

            ifs.close(); 





        }

        /**
         * A function that makes life a bit easier. 
         */
        static bool findInitStr(const std::string & str, const std::string & substr)
        {
            return str.substr(0, substr.size()) == substr; 
        }

        static bool findInitStr(const std::string & str, const std::string & substr, std::string & reststr)
        {
            bool found = false; 
            if ( str.substr(0, substr.size()) == substr)
            {
                found = true; 
                reststr = str.substr(substr.size()-1);
            }
            else 
                reststr = str; 

            return found; 
        }


        /**
         * Split the input eigen matrix which was read with BINARY_V3 to three
         * seperate eigen matrices. 
         */ 
        static void splitDataV3(const Eigen::MatrixXd &D, Eigen::MatrixXd &mat_x,
                                                          Eigen::MatrixXd &mat_y, 
                                                          Eigen::MatrixXd &mat_z) 
        {
            assert (D.cols()%3 == 0);  // in case an incomplete read or wrong identifier when reading

            cout << "Spliting data from Vector3" << endl; 
            int Dactual = D.cols()/3; 

            mat_x.resize(D.rows(), Dactual); 
            mat_y.resize(D.rows(), Dactual); 
            mat_z.resize(D.rows(), Dactual); 

            for (int jj=0; jj<Dactual; jj++)
            {
                mat_x.col(jj) = D.col(jj*3); 
                mat_y.col(jj) = D.col(jj*3 + 1); 
                mat_z.col(jj) = D.col(jj*3 + 2); 
            }
        }

        /** 
         * Extract file names in "directory" filenames of which starts with "startString", return results 
         * in filenames. Will attempt a sort on string names. 
         */ 
        static void listDirectory(const char * directory, const char * startString, vector<string> &filenames)
        {

            DIR *dp;
            struct dirent *dirp;

            if((dp  = opendir(directory)) == NULL) 
            {
                cerr << "Error(" << errno << ") opening " << directory << endl;
                exit(1);
            }


            cout << "Reading filename list from directory : " << directory << endl; 
            cout << "The starting string that is searched for : \"" << startString << "\"" << endl; 
              
            while ((dirp = readdir(dp)) != NULL) 
            {
                string dname = string(dirp->d_name); 

                unsigned int endn = (unsigned) strlen(startString); 
                if (dname.substr(0,endn) == startString)
                {
                    filenames.push_back(dname);
                }
            }

            // sort the file names
            std::sort(filenames.begin(), filenames.end());

            closedir(dp);

            if (filenames.size() == 0) 
                cout << "* There might be some problems, zero files read. " << endl; 
            else 
                cout << "Job finished. " << filenames.size() << " files in directory are read. " << endl; 

        }


        // Split the string s using splitters.  
		static vector<string> split( const string& s, const string& splitters )
		{
			vector<string> splat;
			int start = 0;
			while( 1 )
			{
				size_t occur = s.find_first_of( splitters, start );

				if( occur == string::npos ) {
					// we're done. add the last string
					splat.push_back( s.substr( start, string::npos ) );
					break;
				}
				else {
					splat.push_back( s.substr( start, occur-start ) );
					start = occur + 1;
				}	
			}

			return splat;
		}





}; 


#endif
