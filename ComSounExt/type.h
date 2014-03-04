#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED

#define DWORD unsigned long
#define SHORT short int
#define UINT  unsigned int
#define BYTE  unsigned char

typedef struct {
    BYTE        STR[8];
    long        MaxWav;
    } WLK2HD;

typedef struct {
    long        SP;
    long        SZ;
    long        SR;
    BYTE        A[4];
    BYTE        Z[4];
    } WLK2BODY;

typedef struct {
    long        SP;
    long        SZ;
    long        SR;
    } WLK1BODY;

typedef struct {
    char        riff_id[4];
    DWORD       riff_size;
    char        wave_id[4];
    char        format_id[4];
    DWORD       format_size;
    SHORT       format_type;
    SHORT       channel_mode;
    DWORD       samples_per_sec;
    DWORD       avg_bytes_per_sec;
    SHORT       bytes_per_sample;
    SHORT       bits_per_sample;
    char        data_id[4];
    UINT        data_size;
    } WAVEFILEHDR;

#endif // TYPE_H_INCLUDED

