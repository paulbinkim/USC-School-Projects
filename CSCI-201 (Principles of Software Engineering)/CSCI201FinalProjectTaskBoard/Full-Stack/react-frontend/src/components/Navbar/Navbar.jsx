import React from 'react';
import { Link} from "react-router-dom";
import './Navbar.css';

function Navbar() {
    return (
      <div>
      <nav id="entirebar">
      <Link to="/" id="logo">
        Vision
      </Link>
      <ul>
        
        <li>
          <Link to="/login" className="login-button">
            Login
          </Link>
          
        </li>
        <li>
          <Link to="/history" className="history-button">
            History
          </Link>
        </li>
        <li>
          <Link to="/add-task/_add">
            Create Task
          </Link>
        </li>
        <li>
          <Link to="/add-group/_add">
            Create/Join Group
          </Link>
        </li>
        <li>
          <Link to="/Chat" target="_blank">Global Chat</Link>
        </li>
        <li>
          <Link to="/GroupHome" className="home-button">
            Group Home
          </Link>
          
        </li>
        <li>
          <Link to="/" className="home-button">
            Home
          </Link>
          
        </li>
      </ul>
      </nav>
      </div>
    );
  }
  
  export default Navbar;