extern "C" {
    //kmc_read
    long start_frame, end_frame, framenumber;
    unsigned char filenamebase[200];
    
    void init(char* device);
    int read_multiple_frames();
    
    //kmc_scsi
    int hsize, vsize, fps, totalFrames;
    int kmc_dev_fd(char* device);
}
