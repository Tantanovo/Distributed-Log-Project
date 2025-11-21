#include"appendfile.hpp"
#include<string.h>
#include<cassert>
namespace tulun
{
    //class appendfile
    
        //static const size_t FILE_BUFF_SIZE = 1024 * 128;
        //FILE *fp_;
        //std::unique_ptr<char[]> buff_;
        //size_t writenbytes_; // file total
        size_t appendfile::write(const char *msg, const int len){
            return fwrite_unlocked(msg,sizeof(char),len,fp_);
            //fwrite
        }


        appendfile::appendfile(const std::string &filename)
            :fp_{nullptr},
            buff_{new char[FILE_BUFF_SIZE]},
            writenbytes_(0)
        {   
            fp_=fopen(filename.c_str(),"a");
            assert(fp_!=nullptr);
            setbuffer(fp_,buff_.get(),FILE_BUFF_SIZE);
        };
        appendfile::~appendfile(){
            fclose(fp_);
            fp_=nullptr;
            buff_.reset();
        };
        void appendfile::append(const std::string &msg){
            append(msg.c_str(),msg.size());
        };
        void appendfile::append(const char *msg, const int len){
            size_t n=write(msg,len);
            size_t remain=len-n;
            while(remain>0){
                size_t x=write(msg+n,remain);
                if(0==x){
                    int err=ferror(fp_);
                    if(err){
                        fprintf(stderr,"appendfile::append() failed %s \n",
                        strerror(err));
                        break;
                    }
                }
                n+=x;
                remain=len-n;
            }
            writenbytes_+=n;
        };
        void appendfile::flush(){
            fflush(fp_);
        };
        size_t appendfile::getwritebytes() const{
            return writenbytes_;
        };
    
}