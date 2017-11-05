######################################
#              FUNCTIONS             #
######################################


####  inc_freq_double
#####################

var inc_freq_double = func (val, min, max, inc,pos){
	
	var dec_val = math.mod(val, 100);
	var int_val = int(val) - dec_val ;
	
	if(pos == '0'){
		dec_val = dec_val + inc;
		if (dec_val > 99) { int_val = 00; }
		if (dec_val < 00) { int_val = 99; }
	}
	
	if(pos == '1'){
		int_val = int_val + (inc*10) ;
		if (int_val > max) { int_val = min; }
		if (int_val < min) { int_val = max; }
	}
	
	return int_val + dec_val;
}


####  inc_freq
##############
var inc_freq = func (val, min, max, inc, type){
	var int_val = int(val);
	var dec_val = (val-int_val)*1000;
	if(type=='d'){
		dec_val = dec_val + inc;
	}
	else{
		int_val = int_val + inc ;
		if (int_val > max) { int_val = min; }
		if (int_val < min) { int_val = max; }
	}
	dec_val = math.mod(dec_val, 1000) * 0.001;
	return int_val + dec_val;
}


#####  inc_adf_chanel
##########################
var inc_adf_chanel = func (stkprop, chanel ,min, max){
	var stkproprties ="saitek_radio_panel/"~stkprop;
	
	var switch = getprop(stkproprties);
	if (switch != "0") {
		var proprFreq = "instrumentation/"~chanel~"/frequencies/standby-khz";
		var standby = getprop(proprFreq);
		
		if(switch == "1"){  
			standby = inc_freq_double(standby,min,max,1,'1');
		}
		
		if(switch == "2"){  
			standby = inc_freq_double(standby,min,max,-1,'1');
		}
		
		if(switch == "3"){ 
			standby = inc_freq_double(standby,min,max,1,'0');
		}
		
		if(switch == "4"){ 
			standby = inc_freq_double(standby,min,max,-1,'0');
		}		
		setprop (proprFreq, standby);
	}
	setprop (stkproprties, "0");
}


#####  inc_xpdr_chanel
##########################
var inc_xpdr_chanel = func (stkprop, min, max){
	var stkproprties ="saitek_radio_panel/"~stkprop;
	
	var switch = getprop(stkproprties);
	if (switch != "0") {
		var proprFreq = "/instrumentation/transponder/id-code";
		var standby = getprop(proprFreq);
		
		if(switch == "1"){  
			standby = inc_freq_double(standby,min,max,1,'1');
		}
		
		if(switch == "2"){  
			standby = inc_freq_double(standby,min,max,-1,'1');
		}
		
		if(switch == "3"){ 
			standby = inc_freq_double(standby,min,max,1,'0');
		}
		
		if(switch == "4"){ 
			standby = inc_freq_double(standby,min,max,-1,'0');
		}		
		setprop (proprFreq, standby);
	}
	setprop (stkproprties, "0");
}


#####  inc_freq_chanel
######################
var inc_freq_chanel = func (stkprop, chanel ,min, max){
	var stkproprties ="saitek_radio_panel/"~stkprop;
	
	var switch = getprop(stkproprties);
	if (switch != "0") {
		var proprFreq = "instrumentation/"~chanel~"/frequencies/standby-mhz";
		var standby = getprop(proprFreq);
		
		if(switch == "1"){  
			standby = inc_freq(standby,min,max,1,'i');
		}
		
		if(switch == "2"){  
			standby = inc_freq(standby,min,max,-1,'i');
		}
		
		if(switch == "3"){ 
			standby = inc_freq(standby,min,max,25,'d');
		}
		
		if(switch == "4"){ 
			standby = inc_freq(standby,min,max,-25,'d');
		}		
		setprop (proprFreq, standby);
	}
	setprop (stkproprties, "0");

}

####  sw_button
###############
var sw_button = func (stkprop, chanel) {
	
	var stkproprties ="saitek_radio_panel/"~stkprop;
	var switch = getprop(stkproprties);
	
	if (switch == "1") {
		var proprFreq = "instrumentation/"~chanel~"/frequencies/";
		
		var standby = getprop(proprFreq~"standby-mhz");
		var selected = getprop(proprFreq~"selected-mhz");
		
		setprop (proprFreq~"standby-mhz", selected);
		setprop (proprFreq~"selected-mhz", standby);
	}
	setprop (stkproprties, "0");
}



####  sw_button_adf
###################
var sw_button_adf = func (stkprop, chanel) {
	
	var stkproprties ="saitek_radio_panel/"~stkprop;
	var switch = getprop(stkproprties);
	
	if (switch == "1") {
		var proprFreq = "instrumentation/"~chanel~"/frequencies/";
		
		var standby = getprop(proprFreq~"standby-khz");
		var selected = getprop(proprFreq~"selected-khz");
		
		setprop (proprFreq~"standby-khz", selected);
		setprop (proprFreq~"selected-khz", standby);
	}
	setprop (stkproprties, "0");
}

######################################
#                COM1                #
######################################

var top_com1_sw = func {
	sw_button("top_com1_sw","comm");
}

var top_com1_inc = func {
	inc_freq_chanel("top_com1_inc","comm",118,136);
}
setprop ("saitek_radio_panel/top_com1_sw", "0");
setlistener ("saitek_radio_panel/top_com1_sw", top_com1_sw);
setprop ("saitek_radio_panel/top_com1_inc", "0");
setlistener ("saitek_radio_panel/top_com1_inc", top_com1_inc);

######################################
#                COM2                #
######################################

var top_com2_sw = func {
	sw_button("top_com2_sw","comm[1]");
}

var top_com2_inc = func {
	inc_freq_chanel("top_com2_inc","comm[1]",118,136);
}
setprop ("saitek_radio_panel/top_com2_sw", "0");
setlistener ("saitek_radio_panel/top_com2_sw", top_com2_sw);
setprop ("saitek_radio_panel/top_com2_inc", "0");
setlistener ("saitek_radio_panel/top_com2_inc", top_com2_inc);

######################################
#                NAV1                #
######################################


var top_nav1_sw = func {
	sw_button("top_nav1_sw","nav");
}

var top_nav1_inc = func {
	inc_freq_chanel("top_nav1_inc","nav",108,117);
}

setprop ("saitek_radio_panel/top_nav1_sw", "0");
setlistener ("saitek_radio_panel/top_nav1_sw", top_nav1_sw);
setprop ("saitek_radio_panel/top_nav1_inc", "0");
setlistener ("saitek_radio_panel/top_nav1_inc", top_nav1_inc);
######################################
#                NAV2                #
######################################


var top_nav2_sw = func {
	sw_button("top_nav2_sw","nav[1]");
}

var top_nav2_inc = func {
	inc_freq_chanel("top_nav2_inc","nav[1]",108,117);
}

setprop ("saitek_radio_panel/top_nav2_sw", "0");
setlistener ("saitek_radio_panel/top_nav2_sw", top_nav2_sw);
setprop ("saitek_radio_panel/top_nav2_inc", "0");
setlistener ("saitek_radio_panel/top_nav2_inc", top_nav2_inc);


######################################
#                ADF                 #
######################################
var top_adf_sw = func {
	sw_button_adf("top_adf_sw","adf");
}

var top_adf_inc = func {
	inc_adf_chanel ("top_adf_inc","adf",200,1700);
}

setprop ("saitek_radio_panel/top_adf_sw", "0");
setlistener ("saitek_radio_panel/top_adf_sw", top_adf_sw);
setprop ("saitek_radio_panel/top_adf_inc", "0");
setlistener ("saitek_radio_panel/top_adf_inc", top_adf_inc);

######################################
#                DME                #
######################################
var top_dme_sw = func {
	## nothing 
}
var top_dme_inc = func {
	## nothing 
}

setprop ("saitek_radio_panel/top_dme_sw", "0");
setlistener ("saitek_radio_panel/top_dme_sw", top_dme_sw);
setprop ("saitek_radio_panel/top_dme_inc", "0");
setlistener ("saitek_radio_panel/top_dme_inc", top_dme_inc);

######################################
#                XPDR                #
######################################
var top_xpdr_sw = func {
	#nothing
}
var top_xpdr_inc = func {
	inc_xpdr_chanel("top_xpdr_inc",0000,9999);
}

setprop ("saitek_radio_panel/top_xpdr_sw", "0");
setlistener ("saitek_radio_panel/top_xpdr_sw", top_xpdr_sw);
setprop ("saitek_radio_panel/top_xpdr_inc", "0");
setlistener ("saitek_radio_panel/top_xpdr_inc", top_xpdr_inc);



##################################### BOTTOM ##################################### 

######################################
#                COM1                #
######################################


var bot_com1_sw = func {
	sw_button("bot_com1_sw","comm");
}

var bot_com1_inc = func {
	inc_freq_chanel("bot_com1_inc","comm",118,136);
}

setprop ("saitek_radio_panel/bot_com1_sw", "0");
setlistener ("saitek_radio_panel/bot_com1_sw", bot_com1_sw);
setprop ("saitek_radio_panel/bot_com1_inc", "0");
setlistener ("saitek_radio_panel/bot_com1_inc", bot_com1_inc);

######################################
#                COM2                #
######################################


var bot_com2_sw = func {
	sw_button("bot_com2_sw","comm[1]");
}

var bot_com2_inc = func {
	inc_freq_chanel("bot_com2_inc","comm[1]",118,136);
}
setprop ("saitek_radio_panel/bot_com2_sw", "0");
setlistener ("saitek_radio_panel/bot_com2_sw", bot_com2_sw);
setprop ("saitek_radio_panel/bot_com2_inc", "0");
setlistener ("saitek_radio_panel/bot_com2_inc", bot_com2_inc);

######################################
#                NAV1                #
######################################

var bot_nav1_sw = func {
	sw_button("bot_nav1_sw","nav");
}

var bot_nav1_inc = func {
	inc_freq_chanel("bot_nav1_inc","nav",108,117);
}
setprop ("saitek_radio_panel/bot_nav1_sw", "0");
setlistener ("saitek_radio_panel/bot_nav1_sw", bot_nav1_sw);
setprop ("saitek_radio_panel/bot_nav1_inc", "0");
setlistener ("saitek_radio_panel/bot_nav1_inc", bot_nav1_inc);

######################################
#                NAV2                #
######################################

var bot_nav2_sw = func {
	sw_button("bot_nav2_sw","nav[1]");
}

var bot_nav2_inc = func {
	inc_freq_chanel("bot_nav2_inc","nav[1]",108,117);
}

setprop ("saitek_radio_panel/bot_nav2_sw", "0");
setlistener ("saitek_radio_panel/bot_nav2_sw", bot_nav2_sw);
setprop ("saitek_radio_panel/bot_nav2_inc", "0");
setlistener ("saitek_radio_panel/bot_nav2_inc", bot_nav2_inc);

######################################
#                ADF                 #
######################################
var bot_adf_sw = func {
	sw_button_adf("bot_adf_sw","adf");
}

var bot_adf_inc = func {
	inc_adf_chanel ("bot_adf_inc","adf",200,1700);
}

setprop ("saitek_radio_panel/bot_adf_sw", "0");
setlistener ("saitek_radio_panel/bot_adf_sw", bot_adf_sw);
setprop ("saitek_radio_panel/bot_adf_inc", "0");
setlistener ("saitek_radio_panel/bot_adf_inc", bot_adf_inc);

######################################
#                DME                #
######################################
var bot_dme_sw = func {
	## nothing 
}
var bot_dme_inc = func {
	## nothing 
}

setprop ("saitek_radio_panel/bot_dme_sw", "0");
setlistener ("saitek_radio_panel/bot_dme_sw", bot_dme_sw);
setprop ("saitek_radio_panel/bot_dme_inc", "0");
setlistener ("saitek_radio_panel/bot_dme_inc", bot_dme_inc);

######################################
#                XPDR                #
######################################
var bot_xpdr_sw = func {
	#nothing
}
var bot_xpdr_inc = func {
	
	inc_xpdr_chanel("bot_xpdr_inc",0000,9999);
}

setprop ("saitek_radio_panel/bot_xpdr_sw", "0");
setlistener ("saitek_radio_panel/bot_xpdr_sw", bot_xpdr_sw);
setprop ("saitek_radio_panel/bot_xpdr_inc", "0");
setlistener ("saitek_radio_panel/bot_xpdr_inc", bot_xpdr_inc);














