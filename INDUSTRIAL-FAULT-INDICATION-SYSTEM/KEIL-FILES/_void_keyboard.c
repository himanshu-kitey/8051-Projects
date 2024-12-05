_U8 sub_keypad()
{
	while(i=keypad('*'))
		 { 
			 if(i=='D' && v!=0)
			 {
				 lcd_cmd();
				 pass_str();
				 _lcd_2ndLine();
				 back_loop(--v,pass);
			 }  			
  else  if(v==6)
			 {
          if(i=='#') break;
         else return 1;		
			 }
  else  if(i=='*') return 0;				 
  else  if(i!='#' && i!='D')
		      {
		       pass[v++]=i;
		       _write_data(i);
	   	    }
			}
			 return 2;
}