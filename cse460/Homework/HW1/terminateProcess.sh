processCount=0
id='test1'
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
	echo "Process test1 killed!";
	echo $processCount;
}
else
echo "Process test1 not running!"
fi
