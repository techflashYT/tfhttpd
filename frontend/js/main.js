var servers = [
	"DisNCord",
	"Mineman's Projects",
	"a",
	"b",
	"Your Mom",
	"The Amazing SeshCord server of the Technological Flash",
];
var channels = ["General", "Photos", "Memes", "Off Topic", "Your Dad"];
var members = ["Minivan", "Techflash", "DisNBot"];

var elements = {
	sidebar: undefined,
	channelBar: undefined,
	chatBar: undefined,
	titleBar: undefined,
	membersBar: undefined,
};


function chatBarReset(membersBarVisible) {
	elements.chatBar.style.left = "264px"
	elements.chatBar.style.marginLeft = "10px"
	elements.chatBar.style.marginRight = "10px"
	elements.chatBar.style.paddingLeft = "10px"
	elements.chatBar.style.paddingRight = "3px"
	var widthOffset = 264 + parseInt(elements.chatBar.style.marginLeft) +
		parseInt(elements.chatBar.style.marginRight) +
		parseInt(elements.chatBar.style.paddingLeft) +
		parseInt(elements.chatBar.style.paddingRight)


	if (membersBarVisible) {
		// Adjust the widthOffset to account for the width of the membersBar
		widthOffset += parseInt(elements.membersBar.offsetWidth);
	}

	elements.chatBar.style.width = `calc(100% - ${widthOffset}px)`
}

function sendMessage(message) {
	// Pack JSON object with the following variables
	var json = {
		msg: message,
		token: session.token,
		uid: session.user.id,
		server: session.currentServer.id,
		channel: session.currentServer.currentChannel.id,
	};

	// Send JSON object to the relative path `/v1/msg/s`
	var xhr = new XMLHttpRequest();
	xhr.open("POST", "/v1/msg/s", false);
	xhr.setRequestHeader("Content-Type", "application/json");
	xhr.send(JSON.stringify(json));

	// Return whether it succeeded or failed
	return xhr.status === 200; // Assuming 200 indicates success
}
