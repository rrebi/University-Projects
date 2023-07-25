import * as React from "react";
import { BrowserRouter as Router, Routes, Route } from "react-router-dom";
import { AppHome } from "./components/AppHome";
import { AppMenu } from "./components/AppMenu";
import { PublisherAll } from "./components/publisher/PublisherAll";
import { PublisherAdd } from "./components/publisher/PublisherAdd";
import { PublisherDelete } from "./components/publisher/PublisherDelete";
import { PublisherUpdate } from "./components/publisher/PublisherUpdate";
import { PublisherDetails } from "./components/publisher/PublisherDetails";
import { PublisherAvgBooksStars } from "./components/statistics/PublisherAvgBooksStars";

function App() {
	return (
		<React.Fragment>
			<Router>
				<AppMenu />

				<Routes>
					<Route path="/" element={<AppHome />} />
					<Route path="/publisher/" element={<PublisherAll />} />
					<Route path="/publisher/add" element={<PublisherAdd />} />
					<Route path="/publisher/:publisherID/edit" element={<PublisherUpdate />} />
					<Route path="/publisher/:publisherID/delete" element={<PublisherDelete />} />
					<Route path="/publisher/:publisherID/details" element={<PublisherDetails />} />
					
					<Route path="/publisher/statistics/" element={<PublisherAvgBooksStars/>}></Route>
				</Routes>
			</Router>
		</React.Fragment>
	);
}

export default App;