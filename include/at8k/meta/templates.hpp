#pragma once

namespace at8k::templates {
	const char ctf[] = {
  		#embed "ctf.toml"
	    , 0  // null terminator
	};
	
	const char exploits[] = {
		#embed "exploits.toml"
	    , 0  // null terminator
	};
};