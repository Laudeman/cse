processCount=0
id='robots'
for pid in $(ps -e -f | grep $id | grep -v 'grep' |awk '{print $2}')
do
{
	kill $pid
	((processCount+=1))
}
done
if(($processCount>0));
then
{
	echo "The processes are deleted";
	echo $processCount;
}
else
echo "There are no processes running"
fi
