
#start fastDFS
sudo fdfs_trackerd ./conf/tracker.conf restart
sudo fdfs_storaged ./conf/storage.conf restart

#start redis
redis-server ./conf/redis.conf
