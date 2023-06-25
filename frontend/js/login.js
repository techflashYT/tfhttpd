var backendErrMsg = "Whoops!  You ran into an issue on our side.  Hang tight, we're sorting it out!"

function login(username, password) {
	var hashedPasswordPromise = sha256(password);
  
	// Send JSON object to `/v1/auth/l`
	var xhr = new XMLHttpRequest()
	xhr.open('POST', '/v1/auth/l', true)
	xhr.setRequestHeader('Content-Type', 'application/json')
	xhr.onreadystatechange = function() {
		if (xhr.readyState !== 4) {
			return
		}
		if (xhr.status === 200) {
			// Login request succeeded
			var data = JSON.parse(xhr.responseText)
			session.token = data.token
			if (session.token == null || session.token == undefined) { 
				setErr(backendErrMsg, "Invalid login token.")
				return
			}
			session.user.name = username
			session.user.id = data.id
			try {
				sessionStorage.setItem("session", JSON.stringify(session))
			}
			catch (err) {
				setErr("Error saving session info to session storage, you probably disabled it in your settings.", err)
				return
			}
			location.href = "/home.html"
			return
		}
		if (xhr.status === 502) {
			setErr(backendErrMsg, "Backend timeout")
			return
		}
		else {
			setErr("You ran into some unknown error!  This is probably an issue on our side, so hang tight, we're sorting it out!")
			return
		}
	}

	Promise.all([hashedPasswordPromise])
	  .then(([hashedPassword]) => {
		// Pack `username` and `password` into JSON object
		const loginData = {
			name: username,
			pass: hashedPassword
		}
		xhr.send(JSON.stringify(loginData))
	})
}

function register(username, email, password) {
	var hashedPasswordPromise = sha256(password);

	// Send JSON object to `/v1/auth/l`
	var xhr = new XMLHttpRequest()
	xhr.open('POST', '/v1/auth/r', true)
	xhr.setRequestHeader('Content-Type', 'application/json')
	xhr.onreadystatechange = function() {
		if (xhr.readyState !== 4) {
			return
		}
		if (xhr.status === 200) {
			// register request succeeded
			document.body.innerHTML = "<h1>Account registered</h1>Please <a href='/'>log in</a> with your new credentials."
			return
		}
		if (xhr.status === 400) {
			// failed with error specified in JSON
		}
		if (xhr.status === 502) {
			setErr(backendErrMsg, "Backend timeout")
			return
		}
		else {
			setErr("You ran into some unknown error!  This is probably an issue on our side, so hang tight, we're sorting it out!")
			return
		}
	}

	Promise.all([hashedPasswordPromise])
	  .then(([hashedPassword]) => {
		// Pack `name`, `pass`, and `email` into JSON object
		const loginData = {
			name: username,
			pass: hashedPassword,
			email: email
		}
		xhr.send(JSON.stringify(loginData))
	})
}

function setErr(mainError, extendedError) {
	if(extendedError != undefined) {
		alert(mainError + " Here's the error: " + extendedError)
	}
	else {
		alert(mainError)
	}
}