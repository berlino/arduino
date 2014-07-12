String result;

void setup() 
{
  Serial1.begin(115200);
  Serial1.setTimeout(100);
}

void loop()
{
  result=readline();
  if(result!="")
    Serial1.println(result);
}


String readline()
{
   int tries=0;
   String line;
   String message;
   char buffer[16];
   int begin_pos,end_pos;
   int num;
   while(Serial1.available()>0)
   {
     //Serial1.println(tries);
     num=Serial1.readBytes(buffer,16);
     //Serial1.println(num);
     buffer[num]='\0';
     //Serial1.println(buffer);
     message+=buffer;
     //Serial1.println(message);
     begin_pos=message.indexOf('@');
     //Serial1.println(begin_pos);
     //Serial1.println(message.length());
     end_pos=begin_pos+15;
     if((begin_pos>=0) && (end_pos<=message.length()))
     {
       line=message.substring(begin_pos,end_pos+1);
       //Serial1.println(line);
       return line;
     }
     tries=tries+1;
     if(tries>=10)
       break;
   }
   return line;
}


