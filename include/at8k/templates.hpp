#pragma once

namespace at8k::templates {
	const char ctf[] = {
  		#embed "../../templates/ctf.toml"
	    , 0  // null terminator
	};
	
	const char exploits[] = {
		#embed "../../templates/exploits.toml"
	    , 0  // null terminator
	};
};