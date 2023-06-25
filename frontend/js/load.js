function load() {
	const loadingWrapper = document.createElement("div");
	loadingWrapper.id = "loadingWrapper";
	loadingWrapper.style.visibility = "visible";

	loadingWrapper.innerHTML = '<h3 style="text-align:center">Loading...</h3>';

	document.body.style.margin = "0";
	document.body.appendChild(loadingWrapper);

	const wrapper = document.createElement("div");
	wrapper.id = "wrapper";
	wrapper.style.visibility = "hidden";
	document.body.append(wrapper);

	const sidebar = document.createElement("div");
	sidebar.id = "sidebar";

	const channelBar = document.createElement("div");
	channelBar.id = "channelBar";

	var imagesReady = false;
	for (i = 0; i < servers.length; i++) {
		const btn = document.createElement("button");
		btn.id = "btn";

		btn.title = servers[i];

		const img = document.createElement("img");
		img.id = "img";
		img.setAttribute("src", "assets/seshcord-logo-50px.png");

		// image object to test of the image has finished loading
		var image = new Image();
		image.src = "assets/seshcord-logo-50px.png";

		if (image.complete) {
			imagesReady = true;
		} else {
			//
			image.addEventListener("load", function () {
				console.log("Image has finished loading.");
			});
		}

		btn.appendChild(img);
		sidebar.appendChild(btn);
	}

	const serverName = document.createElement("h2");
	serverName.id = "serverName";
	serverName.innerText = "DisNCord";
	channelBar.appendChild(serverName);

	for (i = 0; i < channels.length; i++) {
		const channelName = document.createElement("h3");
		const channelButton = document.createElement("button");
		const br = document.createElement("br");

		channelName.id = "channelName";
		channelButton.id = "channelButton";

		channelName.innerText = "#" + channels[i];

		channelButton.appendChild(channelName);
		channelBar.appendChild(channelButton);
		channelBar.appendChild(br);
	}

	elements.sidebar = sidebar;
	elements.channelBar = channelBar;

	const chatBar = document.createElement("input");
	elements.chatBar = chatBar;
	chatBar.id = "chatBar";

	chatBar.placeholder = "Enter your message here";

	chatBar.onkeydown = function (event) {
		if (event.key == "Enter") {
			sendMessage(chatBar.value);
			chatBar.value = "";
		}
	};

	const titleBar = document.createElement("div");
	elements.titleBar = titleBar;
	titleBar.id = "titleBar";

	const titleBarText = document.createElement("h3");
	titleBarText.innerText =
		"Off Topic" + " | " + "This is a test channel description";
	titleBar.appendChild(titleBarText);

	titleBar.style.marginLeft = "0px";
	titleBar.style.marginRight = "0px";
	titleBar.style.paddingLeft = "10px";
	titleBar.style.paddingRight = "3px";
	var widthOffset =
		264 +
		parseInt(titleBar.style.marginLeft) +
		parseInt(titleBar.style.marginRight) +
		parseInt(titleBar.style.paddingLeft) +
		parseInt(titleBar.style.paddingRight);
	titleBar.style.width = `calc(100% - ${widthOffset}px)`;

	const membersBar = document.createElement("div");
	elements.membersBar = membersBar;
	membersBar.id = "membersBar";

	for (i = 0; i < members.length; i++) {
		const memberName = document.createElement("h3");
		const memberButton = document.createElement("button");
		const br = document.createElement("br");

		memberName.id = "memberName";
		memberButton.id = "memberButton";

		memberName.innerText = members[i];

		memberButton.appendChild(memberName);
		membersBar.appendChild(memberButton);
		membersBar.appendChild(br);
	}

	const showMembers = document.createElement("button");
	showMembers.id = "showMembers";

	membersBar.style.visibility = "visible";
	var open = true;

	showMembers.onclick = function showMembers() {
		if (!open) {
			open = true;
			membersBar.style.visibility = "visible";
			chatBarReset(true);
		} else {
			open = false;
			membersBar.style.visibility = "hidden";
			chatBarReset(false);
		}
	};

	titleBar.appendChild(showMembers);

	titleBar.style.width = `calc(100% - ${widthOffset}px)`;

	wrapper.appendChild(sidebar);
	wrapper.appendChild(channelBar);
	wrapper.appendChild(membersBar);
	wrapper.appendChild(chatBar);
	wrapper.appendChild(titleBar);
	chatBarReset(true);
	loadingWrapper.style.visibility = "hidden";
	wrapper.style.visibility = "visible";
}
