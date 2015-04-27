#include <sndfile.h> 
#include <Eigen/Dense>

using namespace std; 

class SoundReader
{
    public: 
        static Eigen::MatrixXd * wavreader(const char * wavfile, int BUFFERSIZE, Eigen::MatrixXd * soundout)
        {
            //char wavfile[] = "./sound/test.wav"; 

            printf("Reading wav files : %s\n", wavfile); 
            // read wav files 
            struct SF_INFO *mysf = new SF_INFO(); 
            mysf->format = 0; 
            SNDFILE* mysnd = sf_open(wavfile, SFM_READ, mysf); 

            if (NULL != mysnd) 
                printf(" - Opened successfully! Start reading.\n"); 
            else 
                printf(" - Cannot open wav files. %s\n", sf_strerror(mysnd));


            double readsound[BUFFERSIZE];
            sf_count_t sct = sf_readf_double(mysnd, readsound, BUFFERSIZE);
            printf(" - %i doubles are read from the sound file.\n", (int)sct); 


            cout << " - Writing data to input container." << endl; 
            soundout->setZero(BUFFERSIZE,1);
            for (int ii=0; ii<BUFFERSIZE; ii++)
                (*soundout)(ii) = readsound[ii];

            sf_close(mysnd); 


            return soundout; 
        }

};
