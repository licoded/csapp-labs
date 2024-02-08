## Resources

- [Student site](http://csapp.cs.cmu.edu/3e/students.html)
- [Video Lectures](https://scs.hosted.panopto.com/Panopto/Pages/Sessions/List.aspx#folderID=%22b96d90ae-9871-4fae-91e2-b1627b43e25e%22)

## Lab Assignments

Track your progress through the labs by checking the boxes below:
- [ ] Data Lab
- [ ] Bomb Lab
- [ ] Attack Lab
- [ ] Cache Lab
- [ ] Shell Lab
- [ ] Malloc Lab
- [ ] Proxy Lab

## Reference Solutions

- https://github.com/jlu-xiurui/csapp-labs

## Docker Setup

```bash
docker pull xieguochao/csapp
git clone git@github.com:XieGuochao/csapp.git
docker run -d -p 7777:7777 -v "$PWD/labs:/home/csapp/project" xieguochao/csapp
... # setup tmux zsh-antigen vim
# login as super user to set passwd
docker exec -u 0 -it <container_id/name> bash
```

### final login command

```bash
docker exec -w /home/csapp/project/datalab -it d39a6aa56ba7 /bin/zsh
```
