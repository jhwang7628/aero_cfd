int patestCallback( const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData )
{
    paTestData *data = (paTestData*)userData;
    float *out = (float*)outputBuffer;
    unsigned int i;

    double left_phaseInc = 0.02;
    double right_phaseInc = 0.06;

    double left_phase = data->left_phase;
    double right_phase = data->right_phase;

    (void) statusFlags; /* Prevent unused variable warnings. */
    (void) inputBuffer;

    data->outTime = timeInfo->outputBufferDacTime;

    for( i=0; i<framesPerBuffer; i++ )
    {
        left_phase += left_phaseInc;
        if( left_phase > TWOPI ) left_phase -= TWOPI;
        *out++ = (float) sin( left_phase );

        right_phase += right_phaseInc;
        if( right_phase > TWOPI ) right_phase -= TWOPI;
        *out++ = (float) sin( right_phase );
    }

    data->left_phase = left_phase;
    data->right_phase = right_phase;

    return paContinue;
}

void ReportStreamTime( PaStream *stream, paTestData *data )
{
    PaTime  streamTime, latency, outTime;
    
    streamTime = Pa_GetStreamTime( stream );
    outTime = data->outTime;
    if( outTime < 0.0 )
    {
        printf("Stream time = %8.1f\n", streamTime );
    }
    else
    {
        latency = outTime - streamTime;
        printf("Stream time = %8.4f, outTime = %8.4f, latency = %8.4f\n",
            streamTime, outTime, latency );
    }
    fflush(stdout);
}
