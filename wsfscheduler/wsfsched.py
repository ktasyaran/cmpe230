#!/usr/bin/python

import os
import boto3
import sys
import time
import datetime

"""Implements topological sort and returns list"""
def topS(target,edges):
  newl=[]
  result=[]
  for item in target.keys():
    if target[item]==0:
       newl.append(item)
  while len(newl)!=0:
    ite=newl[0]
    result.append(ite)
    del newl[0]
    for item in edges:
      if item[0]==ite:
        target[item[1]]-=1
        if target[item[1]]==0:
          newl.append(item[1])
  if len(result)==len(target):
    return result
  else:
    return "Cycle!"

"""File input part. Reads input file and gets stuff for topological sorting."""
filN=""
cwd0=os.getcwd()
for fil in os.listdir(cwd0+"/"+sys.argv[1]):
   if fil.endswith(".wdf"):
     filN=fil
os.chdir(cwd0+"/"+sys.argv[1])
fr=open(filN,"r")
lis=fr.readlines()
fr.close()
os.chdir(cwd0)
execpgms={}
index=lis.index("%%\n")
indegree={}
edgel=[]

"""This loop for getting edge list"""
for i in range (len(lis)):
  tempel=lis[i]
  if i<index:
    tempel=tempel.split(": ")
    if not tempel[0] in execpgms:
      execpgms[tempel[0]]=tempel[1].replace("\n","")
  elif i>index:
    tempel=tempel.split(" => ")
    tempel[1]=tempel[1].replace("\n","")
    edgel.append(tempel)
del lis
for ite in execpgms.keys():
  ite=ite.replace("\n","")
  indegree[ite]=0
for item in edgel:
   indegree[item[1]]+=1
topL=topS(indegree,edgel)
dir0=os.getcwd()
ids=[]
scp1=""
scp2=""
ssh1=""

"""Amazon machine connection part using boto3"""
ec2 = boto3.resource('ec2')
response=ec2.create_instances(ImageId='ami-b73b63a0',MinCount=1,MaxCount=1,KeyName='wdf',SecurityGroups=['wdf'],InstanceType='t2.micro')

"""Indicates creation of instance"""
if len(sys.argv)==3:
  print  str(datetime.datetime.now())+" Instance created\n"
time.sleep(30)
instances = ec2.instances.filter(Filters=[{'Name': 'instance-state-name', 'Values':
  ['running']}])
"""Checks instances and sets scp and ssh strings to be available"""
while(1):
  running =0
  instances=ec2.instances.filter(Filters=[{'Name':'instance-state-name',  'Values':
    ['running']}])
  for instance in instances:
     ids.append(instance.id)
     running =1
 
  scp1='scp -o StrictHostKeyChecking=no -i wdf.pem -r ' + sys.argv[1] + ' ec2-user@' +instance.public_dns_name + ":~"
  scp2='scp -o StrictHostKeyChecking=no -i wdf.pem -r  ec2-user@'+instance.public_dns_name+':~/* '+sys.argv[1]
  ssh1='ssh -o StrictHostKeyChecking=no -i wdf.pem ec2-user@'+instance.public_dns_name
  if running:
    break
time.sleep(30)

os.chdir(dir0)
if len(sys.argv)==3:
  print str(datetime.datetime.now()) + " Files transfering"
os.system(scp1)

if len(sys.argv)==3:
  print str(datetime.datetime.now()) + " Workflow will start executing"
"""Executes topological sort in Amazon instance"""
if topL!="Cycle!":
  for token in topL:
    if len(sys.argv)==3:
        print str(datetime.datetime.now())+" "+execpgms[token].split(" ")[0]+" is started executing"
    if len(execpgms[token].split(" "))==1 and execpgms[token].find(".")<0:
      os.system(ssh1+" "+execpgms[token])
    else:
      os.system(ssh1+" "+sys.argv[1]+"/"+execpgms[token])
    if len(sys.argv)==3:
       print str(datetime.datetime.now())+" "+ execpgms[token].split(" ")[0]+" is finished  executing"
if len(sys.argv)==3:
  print str(datetime.datetime.now()) + " Workflow will finish executing"
"""Gets result file"""
os.system(scp2)
if len(sys.argv)==3:
  print str(datetime.datetime.now())+" Files finished copying"
"""Terminates instance"""
ec2.instances.filter(InstanceIds=ids).terminate()
if len(sys.argv)==3:
  print str(datetime.datetime.now())+" Instance terminated"

