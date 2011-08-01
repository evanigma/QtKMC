extern "C" {
    //kmc_read
    long start_frame, end_frame, framenumber;
    unsigned char filenamebase[200];
    
    void init(char* device);
    int read_multiple_frames();
    int read_frame(int number);
    
    //kmc_scsi
    int hsize, vsize, fps, totalFrames;
    int year, month, date, time_hour, time_minute;
    int kmc_dev_fd(char* device);
}
