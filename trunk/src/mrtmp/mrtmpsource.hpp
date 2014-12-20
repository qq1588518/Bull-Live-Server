#ifndef MRTMPSOURCE_HPP
#define MRTMPSOURCE_HPP

#include <MObject>
#include <MHash>
#include <list>

using namespace std;

class MRtmpMessage;
class MRtmpPool;
class BlsRtmpPublisher;

class MRtmpSource : public MObject
{
public:
    MRtmpSource(const MString &url, MObject *parent = 0);
    ~MRtmpSource();

    int onVideo(MRtmpMessage &msg);
    int onAudio(MRtmpMessage &msg);
    int onMetadata(MRtmpMessage &msg);

    int onPublish();
    int onUnPublish();

    void addPool(MRtmpPool *pool);
    void removePool(MRtmpPool *pool);

    static MRtmpSource * findSource(const MString &url);

    /*!
        return whether the source is in use.
    */
    int acquire(const MString &url, bool &res);

    /*!
        release @url stream
    */
    int release(const MString &url);

private:
    void addToGop(MRtmpMessage &msg);
    int dispatch(MRtmpMessage &msg);
    int fastGop(MRtmpPool *pool);
    void release();

private:
    list<MRtmpMessage> m_gop;
    list<MRtmpPool *> m_pools;

    static MHash<MString, MRtmpSource*> m_sources;

    MRtmpMessage *m_videoSh;
    MRtmpMessage *m_audioSh;
    MRtmpMessage *m_metadata;
    MString m_url;
    BlsRtmpPublisher *m_publisher;
    bool m_isActive;
    int m_lockFd;
};

#endif // MRTMPSOURCE_HPP
