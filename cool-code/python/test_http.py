import socket
import re

if __name__ == '__main__':

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(("127.0.0.1",8080))
    server.listen(5)
    while True:
        conn,addr = server.accept()
        print("my_conn:",conn)
        print("my_addr:",addr)

        msg = conn.recv(102400).decode("utf-8")
        print("my_msg:",msg)
        request_lines = msg.splitlines()
        keyWords = re.match(r'[^/]+([^ ]*)', request_lines[0]).group(1)
        print("find the keywords:",keyWords)
        if keyWords == "/mainPage":
            print("Go to the main page")
            f = open("./pages/mainPage.html", "rb")
            htmlContent = f.read()
            f.close()
            head = "HTTP/1.1 200 OK\r\n\r\n"
            conn.sendall(head.encode("utf-8"))
            conn.sendall(htmlContent)
        else:
            conn.sendall(bytes("HTTP/1.1 200 OK\r\n\r\n", "utf-8"))
            conn.sendall(bytes("<h1><font color=red face=Monaco>xiaoyang</font></h1><h2><font color=pink face=Monaco>so lovely</font></h2>", "utf-8"))
            s = "<h1><font size=6 face=Monaco>web request address : " + addr[0] + ":" + str(addr[1]) +"</font></h1>"
            conn.sendall(bytes(s,"utf-8"))
        conn.close()
