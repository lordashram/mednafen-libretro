#ifndef __MDFN_CDACCESS_IMAGE_H
#define __MDFN_CDACCESS_IMAGE_H

class Stream;
class AudioReader;

struct CDRFILE_TRACK_INFO
{
        int32 LBA;
	
	CDUtility::CD_Track_Format_t Format;
	uint32 DIFormat;

        int32 pregap;
	int32 pregap_dv;

	int32 postgap;

	int32 index[2];

	int32 sectors;	// Not including pregap sectors!
        Stream *fp;
	bool FirstFileInstance;
	bool RawAudioMSBFirst;
	long FileOffset;
	unsigned int SubchannelMode;

	uint32 LastSamplePos;

	AudioReader *AReader;
};

class CDAccess_Image : public CDAccess
{
 public:

 CDAccess_Image(const char *path, bool image_memcache);
 virtual ~CDAccess_Image();

 virtual void Read_Raw_Sector(uint8 *buf, int32 lba);

 virtual void Read_TOC(CDUtility::TOC *toc);

 virtual bool Is_Physical(void);

 virtual void Eject(bool eject_status);
 private:

 int32 NumTracks;
 int32 FirstTrack;
 int32 LastTrack;
 int32 total_sectors;
 CDRFILE_TRACK_INFO Tracks[100]; // Track #0(HMM?) through 99

 std::string base_dir;

 void ImageOpen(const char *path, bool image_memcache);
 void Cleanup(void);

 // MakeSubPQ will OR the simulated P and Q subchannel data into SubPWBuf.
 void MakeSubPQ(int32 lba, uint8 *SubPWBuf);

 bool ParseTOCFileLineInfo(CDRFILE_TRACK_INFO *track, const int tracknum, const char *filename, const char *binoffset, const char *msfoffset, const char *length, bool image_memcache);
 uint32 GetSectorCount(CDRFILE_TRACK_INFO *track);
};


#endif
