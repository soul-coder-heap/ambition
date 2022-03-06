import threading
from random import randint
from threading import Thread
from time import time, sleep
glo = 1000
class Account : 
    def __init__(self, thread_name, value) : 
        self._num = thread_name 
        self._value = value
        self.lock = threading.RLock() 
    def read(self, glo) : 
        for x in range(1000) : 
            #self.lock.acquire() 
            time.sleep(0.1) 
            print("NO." + str(x) + " " + threading.current_thread().name + " read value : " + str(self._value) + " global x : " + str(glo))
            #self.lock.release() 
    def write(self, modify, glo) : 
        for x in range(1000) : 
            self.lock.acquire() 
            self._value += modify 
            glo = glo + modify
            #print("NO." + str(x) + " " + threading.current_thread().name + " write value " + str(modify) + ", value is " + str(self._value)) 
            self.lock.release()
            #time.sleep(1) 

def write(account, draw_amount,glo) : 
    account.write(draw_amount,glo)

def read(account,glo) : 
    account.read(glo)

def run1():
    acct = Account("1234567", 1000) 
    threading.Thread(name = '001xxxx', target = write, args =(acct, 70, glo)).start() 
    threading.Thread(name = '002yyyy', target = write, args =(acct, 80, glo)).start() 
    threading.Thread(name = '003yyyy', target = write, args =(acct, 90, glo)).start() 
    threading.Thread(name = 'ffff', target = read, args =(acct, glo)).start()



class DownloadTask(Thread):
    def __init__(self, filename):
        super().__init__()
        self._filename = filename

    def run(self):
        print('开始下载%s...' % self._filename)
        time_to_download = randint(5, 10)
        sleep(time_to_download)
        print('%s下载完成! 耗费了%d秒' % (self._filename, time_to_download))


def main():
    start = time()
    t1 = DownloadTask('Python从入门到住院.pdf')
    t1.start()
    t2 = DownloadTask('Peking Hot.avi')
    t2.start()
    t1.join()
    t2.join()
    end = time()
    print('总共耗费了%.2f秒.' % (end - start))


if __name__ == "__main__":
    #run1()
    main()

