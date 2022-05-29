import React, { Component } from 'react'
import ReactStars from "react-rating-stars-component";
import PageHeader from '../../../common/PageHeader/PageHeader';
import TaskService from '../../../services/TaskService';
import "./TaskCreate.css"

class CreateTaskComponent extends Component {
    constructor(props) {
        super(props)

        this.state = {
            // step 2
            id: this.props.match.params.id,
            taskName: '',
            completedBy: '',
            assignedBy: '',
            description: '',
            difficulty: '',
            completionDate: '',
            groupCode:'',
            completed: false
        }
        this.changeTaskNameHandler = this.changeTaskNameHandler.bind(this);
        this.changeCompletedByHandler = this.changeCompletedByHandler.bind(this);
        this.changeAssignedBy = this.changeAssignedBy.bind(this);
        this.saveOrUpdateTask = this.saveOrUpdateTask.bind(this);
    }

    componentDidMount(){
        if(this.state.id === '_add'){
            return
        }else{
            TaskService.getTaskById(this.state.id).then( (res) =>{
                let task = res.data;
                this.setState({
                    taskName: task.taskName,
                    completedBy: task.completedBy,
                    assignedBy: task.assignedBy,
                    description: task.description,
                    difficulty: task.difficulty,
                    completionDate: task.completionDate,
                    groupCode: task.groupCode,
                    completed: task.completed
                });
                this.deleteTask = this.deleteTask.bind(this);
            });
        }        
    }

    saveOrUpdateTask = (e) => {
        e.preventDefault();
        let task = {
            taskName: this.state.taskName, 
            completedBy: this.state.completedBy, 
            assignedBy: this.state.assignedBy,
            description: this.state.description, 
            difficulty: this.state.difficulty, 
            completionDate: this.state.completionDate, 
            groupCode: this.state.groupCode,
            completed: this.state.completed
        };
        console.log('task => ' + JSON.stringify(task));

        // step 5
        if(this.state.id === '_add'){
            TaskService.createTask(task).then(res =>{
                this.props.history.push('/HomePage');
            });
        }else{
            TaskService.updateTask(task, this.state.id).then( res => {
                this.props.history.push('/HomePage');
            });
        }
    }

    deleteTask(id){
        TaskService.deleteTask(id).then( res => {
            this.setState({tasks: this.state.tasks.filter(task => task.id !== id)});
        });
        this.props.history.push('/HomePage');
    }

    changeTaskNameHandler= (event) => {
        this.setState({taskName: event.target.value});
    }

    changeCompletedByHandler= (event) => {
        this.setState({completedBy: event.target.value});
    }

    changeAssignedBy= (event) => {
        this.setState({assignedBy: event.target.value});
    }

    changeDescriptionHandler= (event) => {
        this.setState({description: event.target.value});
    }

    changeDifficultyHandler= (event) => {
        this.setState({difficulty: event});
    }

    changeCompletionDateHandler= (event) => {
        this.setState({completionDate: event.target.value});
    }

    changeGroupCodeHandler= (event) => {
        this.setState({groupCode: event.target.value});
    }

    cancel(){
        this.props.history.push('/HomePage');
    }

    getTitle(){
        if(this.state.id === '_add'){
            return true;
        }else{
            return false;
        }
    }
    render() {
        return(
            
            <div class = "main">
                
                <PageHeader  name = {this.getTitle() ? "Add Task" : "Update Task"}/>
                <form action="" method="">
                <div className="form-group line">
                    <label id="title" for="title-id">Title: </label>
                    <input type="text" className="form" id="title-id" name="title" placeholder="Task Name" value={this.state.taskName} onChange={this.changeTaskNameHandler}></input>
                    
                </div>
                <div className="form-group line">
                    <label id="member" for="member-id">Assigned To: </label>
                    <input type="text" className="form" id="member-id" name="member" placeholder="Add Member" 
                        value={this.state.completedBy} onChange={this.changeCompletedByHandler}></input>
                    <label id="member" for="member-id">Assigned By: </label>
                    <input type="text" className="form" id="member-id" name="member" placeholder="Add Member" 
                        value={this.state.assignedBy} onChange={this.changeAssignedBy}></input>
                </div>
                <div className="form-group line">
                    <label id="dated" for="date-id">Due Date: </label>
                    <input type="date" className="form" id="date-id" name="date" placeholder="Completion Date" 
                         value={this.state.completionDate} onChange={this.changeCompletionDateHandler}></input>
                </div>
                <div className="form-group line">
                    <label for="description-id">Description: </label>
                </div>
                <div className="form-group line">
                    <textarea align="top" 
                        type="text" 
                        className="form" 
                        id="description-id" 
                        name="description" 
                        placeholder="Add Description"
                        value={this.state.description} onChange={this.changeDescriptionHandler}>

                    </textarea>
                </div>
                <div className="form-group line">
                    <label id="difficulty" for="difficulty-id">Difficulty: </label>
                    <label id="stars" for="stars-id">
                    <ReactStars
                        count={5}
                        onChange={this.changeDifficultyHandler}
                        size={50}
                        isHalf={true}
                        emptyIcon={<i className="far fa-star"></i>}
                        halfIcon={<i className="fa fa-star-half-alt"></i>}
                        fullIcon={<i className="fa fa-star"></i>}
                        activeColor="#ffd700"
                    />
                    </label>
                    <button type="button" className = "save" onClick={this.saveOrUpdateTask}>Save</button>
                    <button type="button" className= "cancel" onClick={this.cancel.bind(this)} >Cancel</button>
                </div>
                </form>
            </div>
        )
    }
}

export default CreateTaskComponent;
