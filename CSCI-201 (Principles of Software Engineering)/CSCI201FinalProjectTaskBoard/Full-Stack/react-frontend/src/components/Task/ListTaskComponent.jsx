import React, { Component } from 'react'
import TaskService from '../../services/TaskService'
import './ListTaskComponent.css'

class ListTaskComponent extends Component {
    constructor(props) {
        super(props)

        this.state = {
                tasks: []
        }
        this.addTask = this.addTask.bind(this);
        this.editTask = this.editTask.bind(this);
        this.deleteTask = this.deleteTask.bind(this);
    }

    deleteTask(id){
        TaskService.deleteTask(id).then( res => {
            this.setState({tasks: this.state.tasks.filter(task => task.id !== id)});
        });
    }
    viewTask(id){
        this.props.history.push(`/view-task/${id}`);
    }
    editTask(id){
        this.props.history.push(`/add-task/${id}`);
    }

    componentDidMount(){
        TaskService.getTasks().then((res) => {
            this.setState({ tasks: res.data});
        });
    }

    addTask(){
        this.props.history.push('add-task/_add');
    }

    render() {
        return (
            <div>
                 <div className = "row">
                    {/* <button className="btn btn-primary" id="addTaskButton" onClick={this.addTask}> Add Task</button> */}
                 </div>
                 <br></br>
                 <div>
                        <table id="listTable" >
                            <thead>
                                <tr style={{borderTop: "solid 1px #6A6A6A", borderLeft: "solid 1px black"}}>
                                    <th> Task Name</th>
                                    <th> Task Completed By</th>
                                    <th> Task Description</th>
                                    <th> Task Difficulty</th>
                                    <th> Task Completion Date</th>
                                    <th> Actions</th>
                                </tr>
                            </thead>
                            <tbody>
                                {
                                    this.state.tasks.map(
                                        task => 
                                        <tr key = {task.id} style={{borderLeft: "solid 1px black"}}>
                                             <td> {task.taskName} </td>   
                                             <td> {task.completedBy}</td>
                                             <td> {task.description}</td>
                                             <td> {task.difficulty}</td>
                                             <td> {task.completionDate}</td>
                                             <td>
                                                 <button onClick={ () => this.editTask(task.id)} className="btn btn-info">Update </button>
                                                 <button style={{marginLeft: "10px"}} onClick={ () => this.deleteTask(task.id)} className="btn btn-danger">Delete </button>
                                                 <button style={{marginLeft: "10px"}} onClick={ () => this.viewTask(task.id)} className="btn btn-info">View </button>
                                             </td>
                                        </tr>
                                    )
                                }
                            </tbody>
                        </table>

                 </div>

            </div>
        )
    }
}

export default ListTaskComponent
