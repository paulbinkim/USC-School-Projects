import React from 'react';
import logo from './logo.svg';
import './App.css';
import Navbar from './components/Navbar/Navbar';
import {BrowserRouter as Router, Route, Switch} from 'react-router-dom'
import Login from './Pages/Login/Login';
import HistoryPage from './Pages/HistoryPage/HistoryPage';
import ListTaskComponent from './components/Task/ListTaskComponent.jsx';
import CreateTaskComponent from './components/Task/CreateTaskComponent.jsx';
import ViewTaskComponent from './components/Task/ViewTaskComponent.jsx';
import Register from './Pages/Register/Register';
import HomePage from './Pages/HomePage/HomePage';
import ListUserComponent from './components/User/ListUserComponent.jsx';
import CreateUserComponent from './components/User/CreateUserComponent.jsx';
import ViewUserComponent from './components/User/ViewUserComponent.jsx';
import ListGroupComponent from './components/Group/ListGroupComponent.jsx';
import CreateGroupComponent from './components/Group/CreateGroupComponent.jsx';
import ViewGroupComponent from './components/Group/ViewGroupComponent.jsx';
import GroupHome from './Pages/GroupHome/GroupHome';
import Chat from './Pages/ChatPage/Chat';

function App() {
  return (
    <div id="BIGDIV">
        <Router>
            <Navbar />
                <div style={{clear: "both"}}>
                    <Switch> 
                          <Route path = "/" exact component = {HomePage}></Route>
                          <Route path="/Login" component ={Login} ></Route>
                          <Route path="/History" component ={HistoryPage} ></Route>
                          <Route path = "/" exact component = {ListTaskComponent}></Route>
                          <Route path = "/tasks" component = {ListTaskComponent}></Route>
                          <Route path = "/add-task/:id" component = {CreateTaskComponent}></Route>
                          <Route path = "/view-task/:id" component = {ViewTaskComponent}></Route>
                          <Route path="/Register" component = {Register}></Route>
                          <Route path = "/" exact component = {ListUserComponent}></Route>
                          <Route path = "/users" component = {ListUserComponent}></Route>
                          <Route path = "/add-user/:id" component = {CreateUserComponent}></Route>
                          <Route path = "/view-user/:id" component = {ViewUserComponent}></Route>
                          <Route path = "/" exact component = {ListGroupComponent}></Route>
                          <Route path = "/groups" component = {ListGroupComponent}></Route>
                          <Route path = "/add-group/:id" component = {CreateGroupComponent}></Route>
                          <Route path = "/view-group/:id" component = {ViewGroupComponent}></Route>
                          <Route path = "/GroupHome" component = {GroupHome }></Route>
                          <Route path = "/Chat" component = {Chat }></Route>
                        
                    </Switch>
                </div>
        </Router>
    </div>
    
  );
}

export default App;
