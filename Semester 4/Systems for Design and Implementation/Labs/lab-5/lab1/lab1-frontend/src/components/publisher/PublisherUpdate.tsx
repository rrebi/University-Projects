import {
    Button,
    Card,
    CardActions,
    CardContent,
    CircularProgress,
    Container,
    IconButton,
    TextField,
  } from "@mui/material";
  import { useEffect, useState } from "react";
  import { Link, useNavigate, useParams } from "react-router-dom";
  import { Publisher } from "../../models/Publisher";
  import ArrowBackIcon from "@mui/icons-material/ArrowBack";
  import axios from "axios";
  import { GlobalURL } from "../../constants";
  
  export const PublisherUpdate = () => {
    const navigate = useNavigate();
    const { publisherID } = useParams();
  
    const [loading, setLoading] = useState(true);
    const [publisher, setPublisher] = useState<Publisher | null>(null);
  
    useEffect(() => {
      const fetchPublisher = async () => {
        try {
          const response = await axios.get<Publisher>(
            `${GlobalURL}/publisher/${publisherID}`
          );
          setPublisher(response.data);
        } catch (error) {
          console.log(error);
        } finally {
          setLoading(false);
        }
      };
      fetchPublisher();
    }, [publisherID]);
  
    const updatePublisher = async (event: { preventDefault: () => void }) => {
      event.preventDefault();
      try {
        await axios.put(`${GlobalURL}/publisher/${publisherID}`, publisher);
        navigate(`/publisher/`);
      } catch (error) {
        console.log(error);
      }
    };
  
  
    return (
      <Container>
        {loading && <CircularProgress />}
  
        {!loading && !publisher && <div>Publisher not found</div>}
  
        {!loading && publisher && (
          <Card>
            <CardContent>
              <IconButton
                component={Link}
                sx={{ mr: 3 }}
                to={`/publisher/${publisherID}`}
              >
                <ArrowBackIcon />
              </IconButton>{" "}
              <form onSubmit={updatePublisher}>
                <TextField
                  value={publisher.publisher}
                  id="publisher"
                  label="publisher"
                  variant="outlined"
                  fullWidth
                  sx={{ mb: 2 }}
                  onChange={(event) =>
                    setPublisher({ ...publisher, publisher: event.target.value })
                  }
                />
                <TextField
                  value={publisher.year}
                  id="year"
                  label="year"
                  variant="outlined"
                  fullWidth
                  sx={{ mb: 2 }}
                  onChange={(event) =>
                    setPublisher({ ...publisher, year: Number(event.target.value) })
                  }
                />
  
                <TextField
                  value={publisher.owner_name}
                  id="owner_name"
                  label="owner name"
                  variant="outlined"
                  fullWidth
                  sx={{ mb: 2 }}
                  onChange={(event) =>
                    setPublisher({ ...publisher, owner_name: event.target.value })
                  }
                />
  
                <TextField
                  value={publisher.format}
                  id="format"
                  label="format"
                  variant="outlined"
                  fullWidth
                  sx={{ mb: 2 }}
                  onChange={(event) =>
                    setPublisher({ ...publisher, format: event.target.value })
                  }
                />
                <TextField
                  value={publisher.country}
                  id="country"
                  label="country"
                  variant="outlined"
                  fullWidth
                  sx={{ mb: 2 }}
                  onChange={(event) =>
                    setPublisher({ ...publisher, country: event.target.value })
                  }
                />
  
                <Button type="submit">Update publisher</Button>
              </form>
            </CardContent>
            <CardActions></CardActions>
          </Card>
        )}
      </Container>
    );
  };