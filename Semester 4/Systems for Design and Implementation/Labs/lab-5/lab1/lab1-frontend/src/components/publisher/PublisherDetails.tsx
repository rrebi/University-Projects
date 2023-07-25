import { Card, CardActions, CardContent, IconButton } from "@mui/material";
import { Container } from "@mui/system";
import { useEffect, useState } from "react";
import { Link, useParams } from "react-router-dom";
import { Publisher } from "../../models/Publisher";
import EditIcon from "@mui/icons-material/Edit";
import DeleteForeverIcon from "@mui/icons-material/DeleteForever";
import ArrowBackIcon from "@mui/icons-material/ArrowBack";
import { GlobalURL } from "../../constants";
import { styled } from '@mui/material/styles';

export const PublisherDetails = () => {
	const { publisherID } = useParams();
	const [publisher, setPublisher] = useState<Publisher>();

	useEffect(() => {
		const fetchPublisher = async () => {
			
			const response = await fetch(`${GlobalURL}/publisher/${publisherID}`);
			const publisher = await response.json();
			setPublisher(publisher);
		};
		fetchPublisher();
	}, [publisherID]);

	return (
		<Container>
			<Card>
				<CardContent>
					<IconButton component={Link} sx={{ mr: 3 }} to={`/publisher`}>
						<ArrowBackIcon />
					</IconButton>{" "}
					<h1>Publisher Details</h1>
					<p>publisher: {publisher?.publisher}</p>
					
                    <p>year: {publisher?.year}</p>
					
					<p>owner name: {publisher?.owner_name}</p>
					
					<p>format: {publisher?.format}</p>

                    <p>country: {publisher?.country}</p>
					
					<p>boks:</p>
					<ol>
						{publisher?.books?.map((books) => (
							<li key={books.id}>
							{[ 
							  `${books.publisher} ${books.name}`,
							  <br key="1" />,
							  `description: ${books.description}`,
							  <br key="2" />,
							  `author: ${books.author}`,
							  <br key="3" />,
							  `review: ${books.review}`,
                              <br key="4" />,
							  `stars: ${books.stars}`,
							]}
						  </li>
							
						))}
					</ol>
				</CardContent>
				<CardActions>
					<IconButton component={Link} sx={{ mr: 3 }} to={`/publisher/${publisherID}/edit`}>
						<EditIcon />
					</IconButton>

					<IconButton component={Link} sx={{ mr: 3 }} to={`/publisher/${publisherID}/delete`}>
						<DeleteForeverIcon sx={{ color: "red" }} />
					</IconButton>
				</CardActions>
			</Card>
		</Container>
	);
};