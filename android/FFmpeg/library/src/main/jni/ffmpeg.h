//
// Created by wlanjie on 16/5/3.
//

#ifndef FFMPEG_FFMPEG_H
#define FFMPEG_FFMPEG_H

#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libavutil/parseutils.h"
#include "libavfilter/avfilter.h"
#include "libavutil/bprint.h"
#include "libavutil/pixdesc.h"
#include "libavutil/eval.h"
#include "libavutil/display.h"
#include "libavfilter/buffersrc.h"
#include "libavfilter/buffersink.h"

typedef struct InputFile {
    AVFormatContext *ic;
} InputFile;

typedef struct InputStream {
    AVStream *st;
    AVCodecContext *dec_ctx;
    struct AVCodec *dec;
    struct InputFilter *filter;
} InputStream;

typedef struct OutputFile {
    AVFormatContext *oc;
} OutputFile;

typedef struct OutputStream {
    AVStream *st;
    AVCodecContext *enc_ctx;
    struct AVCodec *enc;
    int source_index;
    char *avfilter;
    struct OutputFilter *filter;
    int finished;
    uint64_t sync_opts;
} OutputStream;

typedef struct InputFilter {
    AVFilterContext *filter;
    struct InputStream *ist;
    struct FilterGraph *graph;
} InputFilter;

typedef struct OutputFilter {
    AVFilterContext *filter;
    struct OutputStream *ost;
    struct FilterGraph *graph;
} OutputFilter;

typedef struct FilterGraph {
    AVFilterGraph *graph;
    InputFilter *input;
    OutputFilter *output;
} FilterGraph;

extern InputFile *input_file;
extern InputStream **input_streams;
extern int nb_input_streams;
extern OutputFile *output_file;
extern OutputStream **output_streams;
extern int nb_output_streams;

double get_rotation(AVStream *st);
void *grow_array(void *array, int elem_size, int *size, int new_size);

#define GROW_ARRAY(array, nb_elems) \
    array = grow_array(array, sizeof(*array), &nb_elems, nb_elems + 1);

#endif //FFMPEG_FFMPEG_H
