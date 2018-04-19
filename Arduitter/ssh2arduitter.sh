# senza web tunnel
#ssh root@atrent.it -p 62222

# se si vuol anche accedere all'interfaccia web:
#ssh -vvv root@sl-lab.it -p 8080 -L 8000:localhost:80
ssh -v root@sl-lab.it -p 8080 -L 8000:localhost:80
